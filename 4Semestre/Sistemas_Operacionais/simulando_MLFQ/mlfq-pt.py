#! /usr/bin/env python3

import sys
from optparse import OptionParser
import random

# finds the highest nonempty queue
# -1 if they are all empty
def FindQueue():
    q = hiQueue
    while q > 0:
        if len(queue[q]) > 0:
            return q
        q -= 1
    if len(queue[0]) > 0:
        return 0
    return -1

def Abort(str):
    sys.stderr.write(str + '\n')
    exit(1)


#
# PARSE ARGUMENTS
#

parser = OptionParser()
parser.add_option('-s', '--seed', help='semente do gerador de números aleatórios', 
                  default=0, action='store', type='int', dest='seed')
parser.add_option('-n', '--numQueues',
                  help='número de filas do MLFQ (apenas se não usar a opção -Q)', 
                  default=3, action='store', type='int', dest='numQueues')
parser.add_option('-q', '--quantum', help='duração do time slice (apenas se não usar a opção -Q)',
                  default=10, action='store', type='int', dest='quantum')
parser.add_option('-Q', '--quantumList',
                  help='duração do time slice para cada fila, no seguinte formato: x,y,z,... no qual x é o valor para a fila de maior prioridade, y para a segunda maior prioridade, e assim por diante', 
                  default='', action='store', type='string', dest='quantumList')
parser.add_option('-a', '--allotment', help='tamanho da cota em time slices (apenas se não usar a opção -A)',
                  default=1, action='store', type='int', dest='allotment')
parser.add_option('-A', '--allotmentList',
                  help='tamanho da cota para cada fila, no seguinte formato: x,y,z,... no qual x é o valor para a fila de maior prioridade, y para a segunda maior prioridade, e assim por diante',
                  default='', action='store', type='string', dest='allotmentList')
parser.add_option('-j', '--numJobs', default=3, help='quantidade total de jobs (processos) gerados aleatoriamente',
                  action='store', type='int', dest='numJobs')
parser.add_option('-m', '--maxlen', default=100, help='tempo máximo de CPU dos processos gerados aleatoriamente', action='store', type='int',
                  dest='maxlen')
parser.add_option('-M', '--maxio', default=10,
                  help='frequência máxima de operaçãoes de E/S para processos gerados aleatoriamente',
                  action='store', type='int', dest='maxio')
parser.add_option('-B', '--boost', default=0,
                  help='tempo para resetar a prioridade de todos os processos para a prioridade máxima (zero para desabilitar)',
                  action='store', type='int', dest='boost')
parser.add_option('-i', '--iotime', default=5,
                  help='duração de uma operaçãode E/S (constante para todas as E/S da simulação)',
                  action='store', type='int', dest='ioTime')
parser.add_option('-S', '--stay', default=False,
                  help='reseta cota ao iniciar operação de E/S',
                  action='store_true', dest='stay')
parser.add_option('-I', '--iobump', default=False,
                  help='coloca processo no início da fila após finalizar operação de E/S (em vez de colocar no final da fila)',
                  action='store_true', dest='iobump')
parser.add_option('-l', '--jlist', default='',
                  help='lista separada por vírgulas dos processos a serem executados, no seguinte formato ' + \
                  'x1,y1,z1:x2,y2,z2:... no qual x é o instante de chegada do processo,' + \
                  'y é o tempo total de CPU, e z é o intervalo entre operações de E/S deste processo',
                  action='store', type='string', dest='jlist')
parser.add_option('-c', help='calcular a resposta', action='store_true',
                  default=False, dest='solve')

(options, args) = parser.parse_args()

random.seed(options.seed)

# MLFQ: How Many Queues
numQueues = options.numQueues

quantum = {}
if options.quantumList != '':
    # instead, extract number of queues and their time slic
    quantumLengths = options.quantumList.split(',')
    numQueues = len(quantumLengths)
    qc = numQueues - 1
    for i in range(numQueues):
        quantum[qc] = int(quantumLengths[i])
        qc -= 1
else:
    for i in range(numQueues):
        quantum[i] = int(options.quantum)

allotment = {}
if options.allotmentList != '':
    allotmentLengths = options.allotmentList.split(',')
    if numQueues != len(allotmentLengths):
        print('number of allotments specified must match number of quantums')
        exit(1)
    qc = numQueues - 1
    for i in range(numQueues):
        allotment[qc] = int(allotmentLengths[i])
        if qc != 0 and allotment[qc] <= 0:
            print('allotment must be positive integer')
            exit(1)
        qc -= 1
else:
    for i in range(numQueues):
        allotment[i] = int(options.allotment)

hiQueue = numQueues - 1

# MLFQ: I/O Model
# the time for each IO: not great to have a single fixed time but...
ioTime = int(options.ioTime)

# This tracks when IOs and other interrupts are complete
ioDone = {}

# This stores all info about the jobs
job = {}

# seed the random generator
random.seed(options.seed)

# jlist 'startTime,runTime,ioFreq:startTime,runTime,ioFreq:...'
jobCnt = 0
if options.jlist != '':
    allJobs = options.jlist.split(':')
    for j in allJobs:
        jobInfo = j.split(',')
        if len(jobInfo) != 3:
            print('Badly formatted job string. Should be x1,y1,z1:x2,y2,z2:...')
            print('where x is the startTime, y is the runTime, and z is the I/O frequency.')
            exit(1)
        assert(len(jobInfo) == 3)
        startTime = int(jobInfo[0])
        runTime   = int(jobInfo[1])
        ioFreq    = int(jobInfo[2])
        job[jobCnt] = {'currPri':hiQueue, 'ticksLeft':quantum[hiQueue],
                       'allotLeft':allotment[hiQueue], 'startTime':startTime,
                       'runTime':runTime, 'timeLeft':runTime, 'ioFreq':ioFreq, 'doingIO':False,
                       'firstRun':-1}
        if startTime not in ioDone:
            ioDone[startTime] = []
        ioDone[startTime].append((jobCnt, 'JOB BEGINS'))
        jobCnt += 1
else:
    # do something random
    for j in range(options.numJobs):
        startTime = 0
        runTime   = int(random.random() * (options.maxlen - 1) + 1)
        ioFreq    = int(random.random() * (options.maxio - 1) + 1)
        
        job[jobCnt] = {'currPri':hiQueue, 'ticksLeft':quantum[hiQueue],
                       'allotLeft':allotment[hiQueue], 'startTime':startTime,
                       'runTime':runTime, 'timeLeft':runTime, 'ioFreq':ioFreq, 'doingIO':False,
                       'firstRun':-1}
        if startTime not in ioDone:
            ioDone[startTime] = []
        ioDone[startTime].append((jobCnt, 'JOB BEGINS'))
        jobCnt += 1


numJobs = len(job)

print ('Configuração da simulação:')
print ('\tQuantidade de jobs: ',            numJobs)
print ('\tQuantidade de filas:',          numQueues)
for i in range(len(quantum)-1,-1,-1):
    print ('\tCota  para  a fila de prioridade %2d: %3d' % (i, allotment[i]))
    print ('\tTime slice da fila de prioridade %2d: %3d' % (i, quantum[i]))
print ('\tTempo de reset de prioridades: ',           options.boost)
print ('\tDuração de E/S:',          options.ioTime)
print ('\tReset de cota',     not options.stay)
print ('\tVolta para o início da fila após I/O:',          options.iobump)

print ('\n')
print ('Para cada job, três características são fornecidas:')
print ('  startTime : instante em que o job chega no sistema')
print ('  runTime   : tempo total de CPU que o job precisa para terminar')
print ('  ioFreq    : a cada ioFreq unidades de tempo de CPU, o job inicia uma operação de E/S')
print ('              (a duração da operação de E/S é um parâmetro global da simulação)\n')

print ('Lista de jobs:')
for i in range(numJobs):
    print ('  Job %2d: startTime %3d - runTime %3d - ioFreq %3d' % (i, job[i]['startTime'],
                                                                   job[i]['runTime'],
                                                                   job[i]['ioFreq']))
print ()

if options.solve == False:
    print ('Compute a execução do MLFQ para esta carga de trabalho.')
    print ('Pode ser interessante calcular o tempo total de execução e o tempo de resposta para cada processo.')
    print ()
    print ('Execute o programa novamente com a flag -c para obter a resposta.\n')
    exit(0)

# initialize the MLFQ queues
queue = {}
for q in range(numQueues):
    queue[q] = []

# TIME IS CENTRAL
currTime = 0

# use these to know when we're finished
totalJobs    = len(job)
finishedJobs = 0

print ('\nExecução da simulação:\n')

while finishedJobs < totalJobs:
    # find highest priority job
    # run it until either
    # (a) the job uses up its time quantum
    # (b) the job performs an I/O

    # check for priority boost
    if options.boost > 0 and currTime != 0:
        if currTime % options.boost == 0:
            print ('[ tempo %3d ]       RESET DAS PRIORIDADES (a cada %d tempos)' % (currTime, options.boost))
            # remove all jobs from queues (except high queue) and put them in high queue
            for q in range(numQueues-1):
                for j in queue[q]:
                    if job[j]['doingIO'] == False:
                        queue[hiQueue].append(j)
                queue[q] = []

            # change priority to high priority
            # reset number of ticks left for all jobs (just for lower jobs?)
            # add to highest run queue (if not doing I/O)
            for j in range(numJobs):
                # print '-> Boost %d (timeLeft %d)' % (j, job[j]['timeLeft'])
                if job[j]['timeLeft'] > 0:
                    # print '-> FinalBoost %d (timeLeft %d)' % (j, job[j]['timeLeft'])
                    job[j]['currPri']   = hiQueue
                    job[j]['ticksLeft'] = allotment[hiQueue]
            # print 'BOOST END: QUEUES look like:', queue

    # check for any I/Os done
    if currTime in ioDone:
        for (j, type) in ioDone[currTime]:
            q = job[j]['currPri']
            job[j]['doingIO'] = False
            if type == 'JOB BEGINS':
                print ('[ tempo %3d ] JOB %d chegou!' % (currTime, j))
            elif type == "IO_DONE":
                print ('[ tempo %3d ] JOB %d terminou E/S' % (currTime, j))
            else:
                abort()
            if options.iobump == False or type == 'JOB BEGINS':
                queue[q].append(j)
            else:
                queue[q].insert(0, j)

    # now find the highest priority job
    currQueue = FindQueue()
    if currQueue == -1:
        print ('[ tempo %3d ]       CPU ocioso' % (currTime))
        currTime += 1
        continue
            
    # there was at least one runnable job, and hence ...
    currJob = queue[currQueue][0]
    if job[currJob]['currPri'] != currQueue:
        Abort('currPri[%d] does not match currQueue[%d]' % (job[currJob]['currPri'], currQueue))

    job[currJob]['timeLeft']  -= 1
    job[currJob]['ticksLeft'] -= 1

    if job[currJob]['firstRun'] == -1:
        job[currJob]['firstRun'] = currTime

    runTime   = job[currJob]['runTime']
    ioFreq    = job[currJob]['ioFreq']
    ticksLeft = job[currJob]['ticksLeft']
    allotLeft = job[currJob]['allotLeft']
    timeLeft  = job[currJob]['timeLeft']

    print ('[ tempo %3d ] JOB %d executou com PRIORIDADE %d \t\t [ tempo até final do TS %d;  cotas %d;  tempo restante %d (de %d) ]' % \
          (currTime, currJob, currQueue, ticksLeft, allotLeft, timeLeft, runTime))

    if timeLeft < 0:
        Abort('Error: should never have less than 0 time left to run')


    # UPDATE TIME
    currTime += 1

    # CHECK FOR JOB ENDING
    if timeLeft == 0:
        print ('[ tempo %3d ] JOB %d TERMINOU' % (currTime, currJob))
        finishedJobs += 1
        job[currJob]['endTime'] = currTime
        # print 'BEFORE POP', queue
        done = queue[currQueue].pop(0)
        # print 'AFTER POP', queue
        assert(done == currJob)
        continue

    # CHECK FOR IO
    issuedIO = False
    if ioFreq > 0 and (((runTime - timeLeft) % ioFreq) == 0):
        # time for an IO!
        print ('[ tempo %3d ] JOB %d iniciou E/S' % (currTime, currJob))
        issuedIO = True
        desched = queue[currQueue].pop(0)
        assert(desched == currJob)
        job[currJob]['doingIO'] = True
        # this does the bad rule -- reset your tick counter if you stay at the same level
        if options.stay == True:
            job[currJob]['ticksLeft'] = quantum[currQueue]
            job[currJob]['allotLeft'] = allotment[currQueue]
        # add to IO Queue: but which queue?
        futureTime = currTime + ioTime
        if futureTime not in ioDone:
            ioDone[futureTime] = []
        # print ('IO DONE')
        ioDone[futureTime].append((currJob, 'IO_DONE'))
        
    # CHECK FOR QUANTUM ENDING AT THIS LEVEL (BUT REMEMBER, THERE STILL MAY BE ALLOTMENT LEFT)
    if ticksLeft == 0:
        if issuedIO == False:
            # IO HAS NOT BEEN ISSUED (therefor pop from queue)'
            desched = queue[currQueue].pop(0)
        assert(desched == currJob)

        job[currJob]['allotLeft'] = job[currJob]['allotLeft'] - 1

        if job[currJob]['allotLeft'] == 0:
            # this job is DONE at this level, so move on
            if currQueue > 0:
                # in this case, have to change the priority of the job
                job[currJob]['currPri']   = currQueue - 1
                job[currJob]['ticksLeft'] = quantum[currQueue-1]
                job[currJob]['allotLeft'] = allotment[currQueue-1]
                if issuedIO == False:
                    queue[currQueue-1].append(currJob)
            else:
                job[currJob]['ticksLeft'] = quantum[currQueue]
                job[currJob]['allotLeft'] = allotment[currQueue]
                if issuedIO == False:
                    queue[currQueue].append(currJob)
        else:
            # this job has more time at this level, so just push it to end
            job[currJob]['ticksLeft'] = quantum[currQueue]
            if issuedIO == False:
                queue[currQueue].append(currJob)

        


# print out statistics
print ()
print ('Estatísticas:')
responseSum   = 0
turnaroundSum = 0
for i in range(numJobs):
    response   = job[i]['firstRun'] - job[i]['startTime']
    turnaround = job[i]['endTime'] - job[i]['startTime']
    print ('  Job %2d: startTime %3d - tempo de resposta %3d - tempo total de execução %3d' % (i, job[i]['startTime'],
                                                                        response, turnaround))
    responseSum   += response
    turnaroundSum += turnaround

print ('\nTempo de resposta médio: %.2f' % (float(responseSum)/numJobs,))
print ('Tempo de execução médio: %.2f' % (float(turnaroundSum)/numJobs))

print ('')
