package Exercícios.Collections;

import java.util.ArrayList;
import java.util.LinkedList;

public class List {
    public static void main(String[] args) {
        // Assim como no caso de Map e Set e Queue, list é apenas uma interface, não havendo nenhuma implementação
        // Dessa maneira, devemos decidir qual classe que implementa a interface list devemos utilizar:
        // ArrayList, LinkedList (e depois ArrayDequeue) e Vector

        // Declarando nova array list que receberá strings
        // Observe que não é definido um indixe máximo, portanto é uma estrutura dinâmica, 
        // que crescerá seu espaço de memória conforme o usuário adicionar mais elementos
        ArrayList<String> nova_lista = new ArrayList<>();

        // Funções de adicionar e remover -> Observe que a operação de remover requer uma complexidade maior de execução, pois, ao remove rum elemento
        // os elementos de index maior do que ele devem ser movidos para uma casa a menos, então se um elemento de index 3 é removido, os elementos de maior index 4 e 5
        // devem ser movidos para ocupar, agora, as posições de index 3 e 4
        nova_lista.add("A");
        nova_lista.add("B");
        nova_lista.remove("A"); // Deleta A da lista
        // nova_lista.remove(1); -> Em teoria, deleta o elemento de index 1 (B), porém isso não funciona,
        // pois ao remover A primeiro da lista, B vai assumir o index 1
        nova_lista.remove(0);

        // Função contem e vazio
        if(nova_lista.contains("B")){
            System.out.println("A lista contém B");
        }
        if(nova_lista.isEmpty()){
            System.out.println("A lista está vazia");
        }

        nova_lista.clear();


        // Declarando uma lista ligada, portanto seu funcionamento é dinâmico e não necessáriamente ocupam um bloco na memória,
        // mas estão ligadas a partir de ponteiros que apontam para o próximo elemento na lista
        LinkedList<Integer> nova_lista_ligada = new LinkedList<>();

        // Adicionando e removendo elementos -> Observe que a operação de remover nesse caso é muito menos complexa do que quando comparada
        // com a operção em ArraysLists, pois, nesse caso, não é necessário deslocar nenhum elemento, mas sim apenas mudar o ponteiro que aponta para 
        // o proximo da lista
        nova_lista_ligada.add(2);
        nova_lista_ligada.add(45);
        nova_lista_ligada.remove(0); // Perceba que nesse caso, estamos falando do index, não do valor em si
        nova_lista_ligada.remove(Integer.valueOf(45));

        nova_lista_ligada.clear();

    }
}