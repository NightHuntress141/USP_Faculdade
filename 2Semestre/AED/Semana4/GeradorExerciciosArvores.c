#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// estrutura da arvore
typedef struct NO_ {
	struct NO_ *esq;
	struct NO_ *dir;
	int val;
	int bal;
} NO;

// funcoes gerais

NO* criar_no(int val) {
	NO* novo = malloc(sizeof(NO));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->val = val;
	novo->bal = 0;
	return novo;
}

int tamanho(NO* arv) {
	if (arv == NULL) {
		return 0;
	}
	
	return 1 + tamanho(arv->esq) + tamanho(arv->dir);
}

int profundidade(NO* arv) {
	if (!arv) return 0;
	int pesq = profundidade(arv->esq);
	int pdir = profundidade(arv->dir);
	
	if (pesq > pdir) return 1 + pesq;
	else	return 1+ pdir; 
}

int maior_digitos(NO *arv) {
	if (!arv) return 0;
	int n = 0;
	int val = arv->val;
	while (val) {
		n++;
		val /= 10;
	}

	int n_esq = maior_digitos(arv->esq);
	int n_dir = maior_digitos(arv->dir);

	n = (n > n_esq) ? n : n_esq;
	n = (n > n_dir) ? n : n_dir;
	return n;
}

void exibe_nivel(NO *arv, int nivel, int spaces, bool first, int NUMDIGI) {
    if (nivel < 0) {
        return;
    } else if (nivel == 1) {
            
        if (arv) {
            printf("%*d", NUMDIGI * ((first) ? spaces : spaces*2), arv->val);
        } else {
            printf("%*c", NUMDIGI * ((first) ? spaces : spaces*2), ' ');
        }
    } else {
        if (arv) {
            exibe_nivel(arv->esq, nivel-1, spaces, first & true, NUMDIGI);
            exibe_nivel(arv->dir, nivel-1, spaces, false, NUMDIGI);
        } else {
            exibe_nivel(NULL, nivel-1, spaces, first & true, NUMDIGI);
            exibe_nivel(NULL, nivel-1, spaces, false, NUMDIGI);
        }
    }
}

void exibe_nivel_bal(NO *arv, int nivel, int spaces, bool first, int NUMDIGI) {
    if (nivel < 0) {
        return;
    } else if (nivel == 1) {
            
        if (arv) {
            printf("%*d", NUMDIGI * ((first) ? spaces : spaces*2), arv->bal);
        } else {
            printf("%*c", NUMDIGI * ((first) ? spaces : spaces*2), ' ');
        }
    } else {
        if (arv) {
            exibe_nivel_bal(arv->esq, nivel-1, spaces, first & true, NUMDIGI);
            exibe_nivel_bal(arv->dir, nivel-1, spaces, false, NUMDIGI);
        } else {
            exibe_nivel_bal(NULL, nivel-1, spaces, first & true, NUMDIGI);
            exibe_nivel_bal(NULL, nivel-1, spaces, false, NUMDIGI);
        }
    }
}

void exibir_em_nivel(NO* arv, bool show_bal) {
    if (!arv) return;
    int prof = profundidade(arv);
	int NUMDIGI = maior_digitos(arv);
    for (int i = 1; i <= prof; i++) {
        int spaces = 1 << (prof-i);
        exibe_nivel(arv, i, spaces, true, NUMDIGI);
		if (show_bal) {
			printf("%*c", spaces*NUMDIGI, '|');
			exibe_nivel_bal(arv, i, spaces, true, NUMDIGI);
		}
        printf("\n");
    }
}

// funcoes ABB comum

NO* inserir_abb(NO* arv, int novo_valor) {
	if (arv == NULL) {
		return criar_no(novo_valor);
	}
	
	if (novo_valor > arv->val) {
		arv->dir = inserir_abb(arv->dir, novo_valor);
	}
	
	if (novo_valor < arv->val) {
		arv->esq = inserir_abb(arv->esq, novo_valor);
	}
	
	return arv;
}

NO* buscar_abb(NO* arv, int valor_buscado) {
	if (arv == NULL) {
		return NULL;
	}
	
	if (arv->val == valor_buscado) {
		return arv;
	}
	
	if (valor_buscado > arv->val) {
		return buscar_abb(arv->dir, valor_buscado);
	} else {
		return buscar_abb(arv->esq, valor_buscado);
	}
	
}

NO* buscar_com_pai(NO* arv, int valor_buscado, NO **pai) {
	*pai = NULL;
	while (arv != NULL) {
		if (arv->val == valor_buscado) {
			return arv;
		}
		
		*pai = arv;
		if (valor_buscado > arv->val) {
			arv = arv->dir;
		}
		
		if (valor_buscado < arv->val) {
			arv = arv->esq;
		}
	}
	
	return NULL;
}

NO* excluir_abb(NO* arv, int ch_excluir) {
	if (!arv) return NULL;
	NO *excluido, *pai_do_excluido, *substituto;
	excluido = buscar_com_pai(arv, ch_excluir, &pai_do_excluido);
	if (excluido == NULL) return arv;

	if (excluido->dir == NULL) {
		substituto = excluido->esq;
	} else if (excluido->esq == NULL) {
		substituto = excluido->dir;
	} else {
		NO* pai_do_substituto = excluido;
		substituto = excluido->dir;
		
		while (substituto->esq) {
			pai_do_substituto = substituto;
			substituto = substituto->esq;
		}
		
		if (pai_do_substituto != excluido) {
			pai_do_substituto->esq = substituto->dir;
			substituto->dir = excluido->dir;
		}
		substituto->esq = excluido->esq;		
	}
	
	if (pai_do_excluido == NULL) {
		free(excluido);
		return substituto;	
	} else {
		if (pai_do_excluido->esq != NULL &&
			pai_do_excluido->esq->val == excluido->val) {
			pai_do_excluido->esq = substituto;
		} else {
			pai_do_excluido->dir = substituto;
		}
		free(excluido);
		return arv;
	}

}


// codigo AVL

void rotacao_para_esq(NO **p) {
	NO *u = (*p)->dir;
	(*p)->dir = u->esq;
	u->esq = (*p);
	*p = u;
}

void rotacao_para_dir(NO **p) {
	NO *u = (*p)->esq;
	(*p)->esq = u->dir;
	u->dir = (*p);
	*p = u;
}

void tratar_desbalanceamento_dir (NO **arv) {
	NO *p = *arv;
	NO *u = p->dir;
	
	if (u->bal == 1) {
		// CASO RR
		p->bal = 0;
		u->bal = 0;
		rotacao_para_esq(arv);
	} else if (u->bal == -1) {
		// CASO RL
		NO *v = u->esq;
		
		if (v->bal == 0) {
			u->bal = 0;
			p->bal = 0;
		} else if (v->bal == -1) {
			p->bal = 0;
			u->bal = 1;
			v->bal = 0;
		} else { // v-bal == 1
			p->bal = -1;
			u->bal = 0;
			v->bal = 0;
		}
	
		rotacao_para_dir(&(p->dir)); // u
		rotacao_para_esq(arv);
	} else if (u->bal == 0) {
		// CASO R0
		u->bal = -1;
		// p->bal = 1;
		rotacao_para_esq(arv);
	} else {
		printf("Caso nao tratado %s\n", __func__);
	}
}

void tratar_desbalanceamento_esq (NO **arv) {
	NO *p = *arv;
	NO *u = p->esq;
	
	if (u->bal == -1) {
		// CASO LL
		p->bal = 0;
		u->bal = 0;
		rotacao_para_dir(arv);
	} else if (u->bal == 1) {
		// CASO LR
		NO *v = u->dir;
		if (v->bal == 0) {
			p->bal = 0;
			u->bal = 0;
		} else if (v->bal == 1) {
			p->bal = 0;
			u->bal = -1;
			v->bal = 0;
		} else { // v->bal == -1
			p->bal = 1;
			u->bal = 0;
			v->bal = 0;
		}
		
		rotacao_para_esq(&(p->esq)); //u
		rotacao_para_dir(arv); 
	} else if (u->bal == 0) {
		// CASO L0
		u->bal = 1;
		// p->bal = -1;
		rotacao_para_dir(arv);
	} else {
		printf("Caso nao tratado %s\n", __func__);
	}
}

// retorna indicacao se houve aumento de altura
bool inserir_avl(NO **arv, int novo_val) {
	if ((*arv) == NULL) {
		*arv = criar_no(novo_val);
		return true;
	}
	
	NO *aux = *arv;
	if (novo_val == aux->val) {
		return false;
	} else if (novo_val > aux->val) {
		bool aumentou_altura = inserir_avl(&aux->dir, novo_val);
		if (aumentou_altura) {
			switch (aux->bal) {
			case -1:
				aux->bal = 0;
				return false;
			case 0:
				aux->bal = 1;
				return true;
			case 1:
				tratar_desbalanceamento_dir(arv);
				return false;
				break;
			default:
				printf("Caso nao esperado\n");
				break;
			}
		}
	} else { // novo_val < aux->val
		bool aumentou_altura = inserir_avl(&aux->esq, novo_val);
		if (aumentou_altura) {
			switch (aux->bal) {
				case -1:
					tratar_desbalanceamento_esq(arv);
					return false;
					break;
				case 0:
					aux->bal = -1;
					return true;		
				case 1:
					aux->bal = 0;
					return false;
				default:
					printf("Caso nao esperado\n");
					break;
			}
		}
	}
	return false;
}

bool excluir_avl(NO **arv, int val_del) {
	if (*arv == NULL) {
		return false;
	}
	NO *aux = *arv;
	
	if (aux->val == val_del) {
		if (aux->esq == NULL || aux->dir == NULL) {
			NO *subs = (aux->esq == NULL) ? aux->dir : aux->esq;
			*arv = subs;
			free (aux);
			return true;
		} else {
			NO *subs = aux->dir;
			while (subs->esq != NULL) {
				subs = subs->esq;
			}
			aux->val = subs->val;
			val_del = subs->val;
		}
	}
	
	if (val_del >= aux->val) {
		bool diminuiu = excluir_avl(&(aux->dir), val_del);
		if (diminuiu) {
			switch (aux->bal) {
			case -1:
				tratar_desbalanceamento_esq(arv);
				aux = *arv;
				return (aux->bal == 0);
			case 0:
				aux->bal = -1;
				return false;
			case 1:
				aux->bal = 0;
				return true;
			}
		}
	} else {
		bool diminuiu = excluir_avl(&(aux->esq), val_del);
		if (diminuiu) {
			switch (aux->bal) {
			case -1:
				aux->bal = 0;
				return true;			
			case 0:
				aux->bal =1;
				return false;
			case 1:
				tratar_desbalanceamento_dir(arv);
				aux = *arv;
				return (aux->bal == 0);
			}
		}
	}
	return false;
}

// tratemento de opcoes

struct params {
	unsigned int semente;
	int tamanho;
	int max;
	int adicoes;
	int exclusoes;
	enum tipo_arvs {AVL, ABB} tipo_arv;
	bool seq;
	char *argv0;
};

void set_default_param(struct params *p) {
	p->semente = 2024;
	p->tamanho = 10;
	p->max = 100;
	p->adicoes = 1;
	p->exclusoes = 1;
	p->tipo_arv = AVL;
	p->seq = false;
}

void print_params(struct params *p) {
	printf("Adicoes: %d\n", p->adicoes);
	printf("Exclusoes: %d\n", p->exclusoes);
	printf("Semente: %d\n", p->semente);
	printf("Numero de elementos na arvore: %d\n", p->tamanho);
	printf("Tipo arvore %s\n", (p->tipo_arv == AVL) ? "AVL" : "ABB");
	if (p->seq) {
		printf("Geracao sequencial de valores\n");
	} else {
		printf("Geracao aleatoria de valores\n");
		printf("\tcom semente %d\n", p->semente);
		printf("\tvalor maximo gerado %d\n", p->max -1);
	}

}

typedef void (*argfunc) (char*, struct params*);

struct arg {
	char* arg;
	argfunc f;
	bool needparam;
	char *tip;
};

int get_int(char *str, char *errormsg) {
	char *end;

    int i = strtol(str, &end, 10);
    if (*end != '\0') {
        fprintf(stderr, "%s: %s\n", errormsg, str);
        exit(-1);
    }
	return i;
}
void get_seed(char *str, struct params* p) {
    p->semente = get_int(str, "Valor de semente invalido");
}

void get_tipo(char *tipo_str, struct params* p) {
	char *end;

	if (strcasecmp(tipo_str, "AVL") == 0) {
		p->tipo_arv = AVL;
	} else if (strcasecmp(tipo_str, "ABB") == 0) {
		p->tipo_arv = ABB;
	} else {
		fprintf(stderr, "Tipo de arvore deve ser \"ABB\" ou \"AVL\". Valor digitado: %s\n", tipo_str);
        exit(-1);
	}
}

void get_n(char *str, struct params* p) {
    p->tamanho = get_int(str, "Valor de tamanho invalido");
}

void get_max(char *str, struct params* p) {
    p->max = get_int(str, "Valor maximo invalido") + 1;
}

void get_seq(char *str, struct params* p) {
    p->seq = true;
}

void get_add(char *str, struct params* p) {
    p->adicoes = get_int(str, "Valor de adicoes invalido");
}

void get_del(char *str, struct params* p) {
    p->exclusoes = get_int(str, "Valor de exclusoes invalido");
}

void help(char*, struct params*);

struct arg ex_generator_args [] = {
	{"-h",		help,		false, "exibe esta mensagem e sai"},
	{"--seq",	get_seq,	false, "adiciona numeros sequenciamente"},
	{"--seed",	get_seed,	true, "valor da semente"},
	{"--tipo",	get_tipo,	true, "AVL ou ABB"},
	{"-n",		get_n,		true, "tamanho inicial da arvore"},
	{"--max",	get_max,	true, "valor maximo gerado aleatoriamente"},
	{"--add",	get_add,	true, "quantidade de exercicios de adicao"},
	{"--del",	get_del,	true, "quantidade de exercicios de exclusao"},
 };

void help(char *c, struct params* p) {
	printf("Modo de uso:\n");
	printf("%s ", p->argv0);
	for (int i = 0; i < sizeof(ex_generator_args)/sizeof(ex_generator_args[0]); i++) {
		printf("%s ", ex_generator_args[i].arg);
		if (ex_generator_args[i].needparam) {
			printf("<%s> ", ex_generator_args[i].tip);
		}
	}
	printf("\nOnde:\n");
	for (int i = 0; i < sizeof(ex_generator_args)/sizeof(ex_generator_args[0]); i++) {
		if (!ex_generator_args[i].needparam) {
			printf("%s: %s\n", ex_generator_args[i].arg, ex_generator_args[i].tip);
		}
	}
	exit(0);
}

struct arg *find_arg(char *arg_str) {
	for (int i = 0; i < sizeof(ex_generator_args)/sizeof(ex_generator_args[0]); i++) {
		if (strcmp(arg_str, ex_generator_args[i].arg) == 0) {
			return &ex_generator_args[i];
		}
	}
	return NULL;
}

NO *gera_arvore(struct params* p) {
	NO *a = NULL;

	if (p->seq && p->tipo_arv == ABB) {
		for (int i = 0; i < p->tamanho; i++) {
			a = inserir_abb(a, i+1);
		}
	}
	if (!p->seq && p->tipo_arv == ABB) {
		while (tamanho(a) < p->tamanho) {
			a = inserir_abb(a, rand()%p->max);
		}
	}
	if (p->seq && p->tipo_arv == AVL) {
		for (int i = 0; i < p->tamanho; i++) {
			inserir_avl(&a, i+1);
		}
	}
	if (!p->seq && p->tipo_arv == AVL) {
		while (tamanho(a) < p->tamanho) {
			inserir_avl(&a, rand()%p->max);
		}		
	}
	if (p->tipo_arv == AVL) {
		exibir_em_nivel(a, true);
	} else {
		exibir_em_nivel(a, false);
	}
	return a;
}

void ex_inserir(NO **arv, struct params *p) {
	NO* buscado = NULL;
	int val;
	do {
		val = rand() % p->max;
		buscado = buscar_abb(*arv, val);
	} while (buscado != NULL);
	
	printf("\n");
	printf("Insira o valor %d na arvore %s acima...\n", val, (p->tipo_arv == AVL) ? "AVL" : "ABB");
	printf("Pressione ENTER para continuar e mostrar a resposta\n");
	getchar();
	
	if (p->tipo_arv == AVL) {
		inserir_avl(arv, val);
		exibir_em_nivel(*arv, true);
	} else {
		*arv = inserir_abb(*arv, val);
		exibir_em_nivel(*arv, false);
	}
}

void ex_excluir(NO **arv, struct params *p) {
	NO* buscado = NULL;
	int val;
	do {
		val = rand() % p->max;
		buscado = buscar_abb(*arv, val);
	} while (buscado == NULL);
	
	printf("\n");
	printf("Exclua o valor %d na arvore %s acima...\n", val, (p->tipo_arv == AVL) ? "AVL" : "ABB");
	printf("Pressione ENTER para continuar e mostrar a resposta\n");
	getchar();
	
	if (p->tipo_arv == AVL) {
		excluir_avl(arv, val);
		exibir_em_nivel(*arv, true);
	} else {
		*arv = excluir_abb(*arv, val);
		exibir_em_nivel(*arv, false);
	}
}

int main(int argc, char** argv) {
	
	struct params myparams = {.argv0 = argv[0]};
	set_default_param(&myparams);

	int arg_i = 1;
	while (arg_i < argc) {
		struct arg *myarg = find_arg(argv[arg_i]);
		char *extra = NULL;

		if (myarg == NULL) {
			fprintf(stderr, "Parametro desconhecido: %s\n", argv[arg_i]);
			exit(-1);
		}

		if (myarg->needparam) {
			arg_i++;
			if (arg_i >= argc) {
				fprintf(stderr, "Argumento %s precisa de um valor!\n", argv[--arg_i]);
				exit(-1);
			}
			extra = argv[arg_i];
		}
		myarg->f(extra, &myparams);
		arg_i++;
	}

	if (myparams.seq) {
		myparams.max = myparams.tamanho + myparams.adicoes;
	}
	print_params(&myparams);
	if (!myparams.seq && myparams.max < myparams.tamanho) {
		printf("Max deve ser maior que o tamanho!\n");
		exit(-1);
	}
	printf("\n");

	srand(myparams.semente);
	NO* arv = gera_arvore(&myparams);

	int i;
	for (i = 0; i < myparams.adicoes && tamanho(arv) < myparams.max; i++)
		ex_inserir(&arv, &myparams);
	if (i < myparams.adicoes) {
		printf("\n");
		printf("Nao foi possivel gerar todas as adicoes. Aumente --max ou diminua -n");
		printf("\n");
	}

	for (int i = 0; i < myparams.exclusoes && tamanho(arv) >= 1; i++)
		ex_excluir(&arv, &myparams);
	if (i < myparams.exclusoes) {
		printf("\n");
		printf("Nao foi possivel gerar todas as exclusoes. Aumente -n %d", i);
		printf("\n");
	}

	return 0;
}