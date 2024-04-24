#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "SortingAlgorithm.hpp"
#include <array>

using namespace std;


template<typename T>
double DurationBubble(vector<T>& v){
    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now(); //prendo il tempo ora
    SortLibrary::BubbleSort(v);
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    double duration=std::chrono::duration_cast<std::chrono::nanoseconds>(t_end-t_begin).count();// converto nell'unità di misura che mi interessa e vedo la differenza di tempo
    return duration;
}

template<typename T>
double DurationMerge(vector<T>& v){
    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now();
    SortLibrary::MergeSort(v);
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    double duration=std::chrono::duration_cast<std::chrono::nanoseconds>(t_end-t_begin).count();
    return duration;
}


int main(int argc, char **argv) //argv è il vettore degli argomenti di lunghezza argc
{
    //CONFRONTO DEI TEMPI DI ORDINAMENTO CON BUBBLESORT E MERGESORT
    const int nTimes=10; //quante prove faccio per ogni tipo di vettore

    //VETTORE GIA' ORDINATO CRESCENTE
    cout<<"VETTORE ORDINATO CRESCENTE:"<<endl;
    unsigned int dim = stoi(argv[1]); //trasformo stringa in int
    vector<int> v1(dim); //inizializzo un vettore di dimensione dalla command window
    unsigned int n=1;
    generate(v1.begin(), v1.end(), [&n] () {return n++;});


    double sumB=0.0;
    double sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v1);
    }
    double meanB=sumB/nTimes;
    double meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;

    //se è già ordinato, Bubble è molto più veloce--> O(n) contro O(nlogn)
    cout<<"Bubble molto piu' veloce--> O(n) contro O(nlogn)"<<endl;

    //VETTORE DECRESCENTE
    cout<<endl<<"VETTORE ORDINATO DECRESCENTE:"<<endl;

    sumB=0.0;
    sumM=0.0;
    vector<int> v2;
    for(unsigned int i=0; i<nTimes;i++){
        n=dim;
        generate(v1.begin(), v1.end(), [&n] () {return n--;});
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge non aumenta molto, Bubble si: Merge piu' veloce"<<endl;



    //VETTORE CRESCENTE CON IL PRIMO 1/4 RANDOM
    cout<<endl<<"VETTORE ORDINATO CON PRIMO 1/4 RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;
        generate(v1.begin(), v1.end(), [&n] () {return n++;});

        for(unsigned int j=0; j<(dim/4);j++){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim>500"<<endl;

    //VETTORE CRESCENTE CON ULTIMO 1/4 RANDOM
    cout<<endl<<"VETTORE ORDINATO CON ULTIMO 1/4 RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;
        generate(v1.begin(), v1.end(), [&n] () {return n++;});

        for(unsigned int j=dim-1; j>(dim/4);j--){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim>150"<<endl;

    //VETTORE CRESCENTE CON IL PRIMO E L'ULTIMO 1/4 RANDOM
    cout<<endl<<"VETTORE ORDINATO CON PRIMO E L'ULTIMO 1/4 RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;
        generate(v1.begin(), v1.end(), [&n] () {return n++;});

        for(unsigned int j=0; j<(dim/4);j++){
            v1[j]=rand() % dim;
        }
        for(unsigned int j=dim-1; j>(dim*3/4);j--){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim>150"<<endl;

    //VETTORE CRESCENTE CON PRIMA 1/2 RANDOM
    cout<<endl<<"VETTORE ORDINATO CON PRIMA 1/2 RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;
        generate(v1.begin(), v1.end(), [&n] () {return n++;});

        for(unsigned int j=0; j<(dim/2);j++){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim>300"<<endl;


    //VETTORE CRESCENTE CON SECONDA 1/2 RANDOM
    cout<<endl<<"VETTORE ORDINATO CON SECONDA 1/2 RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;
        generate(v1.begin(), v1.end(), [&n] () {return n++;});

        for(unsigned int j=dim-1; j>(dim/2);j--){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim>150"<<endl;

    //VETTORE RANDOM
    cout<<endl<<"VETTORE RANDOM:"<<endl;
    sumB=0.0;
    sumM=0.0;
    for(unsigned int i=0; i<nTimes;i++){
        n=1;

        for(unsigned int j=0; j<dim;j++){
            v1[j]=rand() % dim;
        }
        v2 = v1; //li devo rifissare ogni volta perchè li riordino
        //BUBBLE
        sumB=sumB+DurationBubble(v1);

        //MERGE
        sumM=sumM+DurationMerge(v2);
    }
    meanB=sumB/nTimes;
    meanM=sumM/nTimes;
    cout<<"Bubble: "<<meanB<<endl;
    cout<<"Merge: "<<meanM<<endl;
    cout<<"Merge piu' rapido circa da dim leggermente >100"<<endl;

    cout<<endl<<"Riassumendo, "<<endl;
    cout<<"Merge tende a rimanere stabile a prescindere dal vettore."<<endl;
    cout<<"Bubble impiega molto poco tempo se il vettore e' gia' ordinato,"<<endl;
    cout<<"Mentre impiega molto soprattutto se non e' ordinata la parte finale del vettore."<<endl;
    cout<<"In generale i risultati valgono sia con release che debug ma con release l'ordinamento e' molto piu' veloce."<<endl;

    return 0;
}

