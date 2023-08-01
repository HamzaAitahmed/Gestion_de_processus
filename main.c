#include <stdio.h>
#include <stdlib.h>

                            // Hamza AitAhmed
							// 2APG4 EMSI Orangers , Casablanca , Maroc
							// 2022/2021

typedef struct node
{
    char type;
    int taille;
    int nbr;
    struct node *next;
}node;

node *head = NULL , *fl = NULL ; // Des liste chainée

node *addhead() // cree un bloc pour un processus dans la memoire
{
    node *n = (node*)malloc( sizeof(node) );
    n->next = NULL;
    n->type = 'O';

    return n;
}

node *addfl() // cree un bloc pour un processus la fil d'attente
{
    node  *temp1 = fl, *n = (node*)malloc( sizeof(node) );

    n->type = 'F';
    n->next = NULL;

    if(fl == NULL)
    {
        fl = n;
    }
    else
    {
        while(temp1->next != NULL)
        {
            temp1 = temp1->next ;
        }
        temp1->next = n;
    }

    return n;
}

/*
	le compactage est une fonction qui compte la taille totale des blocs libres 
	et élimine tous les blocs libres en mémoire et ajoute un bloc en mémoire 
	qui est libre et sa taille est égale à la taille totale des blocs libres qui sont éliminés
*/
void compactage()  
{
    int taille=0;
    node *temp11 , *temp12 ;

    node *n = (node *)malloc(sizeof(node) ); // créer un bloc pour remplacer tous les blocs libres dans un seul bloc qui est n

    n->next = NULL;
    n->type = 'L';

    temp11 = head;
    temp12 = temp11;
    if(temp11->next != NULL)
    {
        while(temp11 != NULL)  //pour éliminer les blocs libres et les remplacer tous dans un seul bloc
        {
            if(temp11->type == 'L')  // c'est pour verifier si Le 1 er bloc est libre
            {
                if(temp11 == temp12)
                {
                    taille += temp11->taille ;
                    head = temp11->next;
                    free(temp11);
                    temp11 = head;
                    temp12 = temp11;
                }
                else
                {
                    taille += temp11->taille ;
                    temp12->next = temp11->next;
                    free(temp11);
                    temp11 = temp12->next;
                }
            }
            else
            {
                temp12 = temp11;
                temp11 = temp11->next;
            }
        }
        if(head==NULL)
            head = n;
        else
            temp12->next = n;

        n->taille = taille; //  après avoir supprimer les blocs libres et compter leur taille
    }

}


void afficher()
{
    node *temp22 = fl, *temp11 = head ;

    printf(" La Memoire :  \n");
    printf(" --------------- \n");
    while(temp11 != NULL)
    {
        if(temp11->type == 'O')
        {
            printf("|\tP%d\t|    ->\ttaille : %d\n", temp11->nbr , temp11->taille);
            printf(" --------------- \n");
        }
        else
        {
            printf("|\t%d\t|\n", temp11->taille);
            printf(" --------------- \n");

        }
        temp11 = temp11->next ;
    }
    printf("\n\n");

    if(fl!=NULL)
    {
        printf(" La File D'attente :  \n");
        printf(" --------------- \n");

        while(temp22 != NULL)
        {
            printf("|\tP%d\t|    ->\ttaille : %d\n", temp22->nbr , temp22->taille);
            printf(" --------------- \n");
            temp22 = temp22->next ;
        }
        printf("\n\n");
    }
    printf(" ############################################################################ \n");
    printf("\n");
}

/*
	Si on ( + ) on a 3 etapes 
	1 - ajouter le proecssus dans la memoire directement s'il y a un bloc libre est sa taille et superieur a la taille du processus sinon on passe a la 2eme etape
	2 - si la taille du processus est superieure a la taille totale des blocs libres on fait le compactage sinon on passe a la 3eme etape
	3 - ajouter le processus dans la fil d'attente 

	Si on ( - ) on 3 etapes
	1 - trouver le processus qu'on va liberer
	2 - trouver le processus qui a la petite taille SJF ( Short Job First ) dans FL ( la fil d'attente)
	3 - ajouter ce processus dans head ( la memoire ) s'il ya un bloc libre qui la taille sup ou egale a la taille du processus sinon
	4 - compactage si on peut ajouter le proecssus dans head ( la memoire )
	5 - afficher()
	
	On passe au processus suivant qui est dans le fichier tailleoriginal.txt

*/
void BestFit(FILE *p)
{
    node *temp1 , *temp2 , *temp3 , *temp4 , *temp5 , *temp6 ;
    int x , i , y , max , min , jpos , jhead , jfl , taille_total;
    char c,b,f;
    i=1;
    while(f != EOF)
    {
        fscanf(p,"%c%d%c",&c,&x,&b);
        f = fgetc(p);
        if(f != EOF)
        {
            if(c=='+') //  si on a ( + )
            {
                printf("\t\t##  On A %c%d%c\n\n",c,x,b);
                jhead=0;

                if(fl==NULL)
                {
                    temp1 = head;
                    temp2 = temp1;
                    temp3 = temp1;
                    temp4 = temp1;
                    jpos  = 0;
                    y = 0;
                    taille_total = 0 ;

                    while(temp1!=NULL && jpos==0) // pour trouver la meilleur zone libre
                    {
                        if(temp1->type == 'L' )
                        {
                            taille_total += temp1->taille ;
                            if(x <= temp1->taille )
                            {
                                if(y==0)
                                {
                                    temp3 = temp1;
                                    temp4 = temp2;
                                    max = temp1->taille;
                                    y=1;
                                }
                                if(x == temp1->taille)
                                {
                                    temp3 = temp1;
                                    temp4 = temp2;
                                    max   = temp1->taille;
                                    jpos=1;
                                }
                                else
                                {
                                    if(max > temp1->taille)
                                    {
                                        temp3 = temp1;
                                        temp4 = temp2;
                                        max = temp1->taille;
                                    }
                                }
                            }
                        }
                        temp2 = temp1;
                        temp1 = temp1->next;
                    }

                    if( temp3->type=='L' )
                    {
                        if( x <= temp3->taille )
                        {
                            if(x == temp3->taille)
                            {
                                temp3->type = 'O';
                                temp3->nbr = i;
                            }
                            else
                            {
                                if(temp3==temp4)
                                {
                                    temp1 = addhead();
                                    temp1->nbr = i;
                                    temp1->taille = x;
                                    temp3->taille -= x;
                                    temp1->next = temp3;
                                    head = temp1;
                                }
                                else
                                {
                                    temp1 = addhead();
                                    temp1->nbr = i;
                                    temp1->taille = x;
                                    temp3->taille -= x;
                                    temp4->next = temp1;
                                    temp1->next = temp3;
                                }
                            }
                            i++;
                            jhead=1;
                        }
                    }

                    if(jhead==0)  // compactage ....
                    {
                        if(x <= taille_total )
                        {
                            compactage();
                            temp1 = head;
                            temp2 = temp1;
                            while(temp1!=NULL && jhead==0)
                            {
                                if(temp1->type == 'L')
                                {
                                    if( x <= temp1->taille )
                                    {
                                        if(x == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = i;
                                            temp2 = temp1;
                                            temp1 = temp1->next;
                                        }
                                        else
                                        {
                                            temp3 = addhead();
                                            temp3->nbr = i;
                                            temp3->taille = x;
                                            temp1->taille -= x;
                                            temp2->next = temp3;
                                            temp3->next = temp1;
                                            temp2 = temp3;
                                        }
                                        i++;
                                        jhead=1;
                                    }
                                    else
                                    {
                                        temp2=temp1;
                                        temp1 = temp1->next;
                                    }
                                }
                                else
                                {
                                    temp2=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                        }
                    }
                }
                if(jhead==0) // ajouter dans la fl ...
                {
                    temp1 = addfl();
                    temp1->taille = x;
                    temp1->nbr = i;
                    i++;
                }
                 //fl ...
            }
            else  // si on a ( - )
            {
                printf("\t\t  On A %c%d%c ## \n\n",c,x,b);
                temp1 = head;
                jhead=0;
                int flp=0;
                while(temp1!=NULL && jhead==0) // trouver le processus qu'on va liberer
                {
                    if( x == temp1->taille )
                    {
                        temp1->type = 'L';
                        jhead=1;
                    }
                    temp1 = temp1->next;
                }

                temp1 = fl;
                temp2 = temp1;
                while(temp1!=NULL && flp==0) // trouver la processus a liberer dans FL si processus n'a pas trouvé un bloc dans la memoire et doit etre liberer
                {
                    if( x == temp1->taille )
                    {
                        if( temp2==temp1)
                        {
                            fl = temp1->next;
                            free(temp1);
                        }else
                        {
                            temp2->next = temp1->next;
                            free(temp1);
                        }
                        jhead=1;
                        flp=1;
                    }else
                    {
                        temp2 = temp1;
                        temp1 = temp1->next;
                    }
                }
            }
            jfl=0;
            jhead=0;
            while(jfl==0 && fl!=NULL)
            {
                jfl=1;
                temp1 = fl;
                temp2 = temp1;
                temp3 = temp1;
                temp4 = temp1;
                min = temp1->taille;

                while(temp1!=NULL)  // boocle SJF  ( short job first )
                {
                    if(min > temp1->taille)
                    {
                        temp2 = temp1;
                        temp3 = temp4;
                        min   = temp1->taille;
                    }
                    temp4 = temp1;
                    temp1 = temp1->next;
                }

                taille_total = 0;
                temp1 = head;
                temp4 = temp1;
                temp5 = temp1;
                temp6 = temp1;
                jpos  = 0;
                y  =  0;

                while(temp5!=NULL && jpos==0) // pour trouver la meilleur zone libre
                {
                    if(temp5->type == 'L' )
                    {
                        taille_total += temp5->taille;
                        if(temp2->taille <= temp5->taille )
                        {
                            if(y==0)
                            {
                                temp1 = temp5;
                                temp4 = temp6;
                                max = temp1->taille;
                                y=1;
                            }
                            if(temp2->taille == temp5->taille) //  temp2 est pointée dans la boocle  SJF
                            {
                                temp1 = temp5;
                                temp4 = temp6;
                                jpos=1;
                            }
                            else
                            {
                                if(max > temp5->taille)
                                {
                                    temp1 = temp5;
                                    temp4 = temp6;
                                    max   = temp5->taille;
                                }
                            }
                        }
                    }
                    temp6 = temp5;
                    temp5 = temp5->next;
                }

                jhead=0;

                if(temp1->type == 'L')
                {
                    if(temp2->taille <= temp1->taille)
                    {
                        if(temp2==temp3) // fl to head ....
                        {
                            if(temp2->taille == temp1->taille)
                            {
                                fl = temp2->next;
                                temp1->type = 'O';
                                temp1->nbr = temp2->nbr;
                                free(temp2);
                            }
                            else
                            {
                                if(temp1 == temp4)    //  si le bloc libre est le 1er bloc dans la liste head  ( la memoire )
                                {
                                    fl = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    head = temp2;
                                }
                                else             //        si le bloc libre est au milieu dans la liste head  ( la memoire )
                                {
                                    fl = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    temp4->next = temp2;
                                }
                            }
                        }
                        else  // si le processus est au milieu de la FL ( fil d'attente )
                        {
                            if(temp2->taille == temp1->taille)   // si la taille du processus est la meme taille du bloc libre dans la liste head ( la memoire )
                            {
                                temp3->next = temp2->next;
                                temp1->type = 'O';
                                temp1->nbr = temp2->nbr;
                                free(temp2);
                            }
                            else
                            {
                                if(temp1 == temp4)    //   si le bloc libre est le 1er bloc dans la liste head  ( la memoire )
                                {
                                    temp3->next = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    head = temp2;
                                }
                                else                 //    si le zone libre est au milieu dans la liste head  ( la memoire )
                                {
                                    temp3->next = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    temp4->next = temp2;
                                }
                            }
                        }
                        jfl=0;
                        jhead=1;
                    }
                }
                if(jhead == 0)  // compactage ... pour ajouter processus qui est on fl dans head si la taille totale des blocs libres est sup au taille du processus
                {
                    if(temp2->taille <= taille_total )
                    {
                        compactage();
                        temp1 = head;
                        temp4 = temp1;
                        while(temp1!=NULL && jhead==0)
                        {
                            if(temp1->type == 'L')
                            {
                                if( temp2->taille <= temp1->taille )
                                {
                                    if(temp3==temp2)
                                    {
                                        fl = temp2->next;
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                    else
                                    {
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp3->next = temp2->next;
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                jhead=1;
                                }
                                else
                                {
                                    temp4=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                            else
                            {
                                temp4=temp1;
                                temp1 = temp1->next;
                            }
                        }
                    }
                }
            }

            afficher();
        }
    }
}

void FirstFit(FILE *p)
{
    node *temp1 , *temp2 , *temp3 , *temp4 ;
    int x , i , min , jhead , jfl , taille_total;
    char c,b,f;

    i=1;
    while(f != EOF)
    {
        fscanf(p,"%c%d%c",&c,&x,&b);
        f = fgetc(p);
        if(f != EOF)
        {
            if(c=='+') // si on a ( + )
            {
                printf("\t\t  On A +%dk\n\n",x);
                jhead=0;
                if(fl==NULL)
                {
                    temp1 = head ;
                    temp2 = temp1 ;
                    taille_total = 0 ;

                    ////printf("La ligne   140 \n");
                    while(temp1!=NULL && jhead==0)  // ajouter dans la memoire
                    {
                        if(temp1->type == 'L')
                        {

                            taille_total += temp1->taille ;
                            if( x <= temp1->taille )
                            {

                                if(x == temp1->taille)
                                {
                                    temp1->type = 'O';
                                    temp1->nbr = i;
                                    temp2 = temp1;
                                    temp1 = temp1->next;
                                }
                                else
                                {
                                    if(temp1==temp2)
                                    {
                                        temp3 = addhead();
                                        temp3->nbr = i;
                                        temp3->taille = x;
                                        temp1->taille -= x;
                                        temp3->next = temp1;
                                        head = temp3;
                                        temp1=head;
                                        temp2=temp1;
                                    }
                                    else
                                    {
                                        temp3 = addhead();
                                        temp3->nbr = i;
                                        temp3->taille = x;
                                        temp1->taille -= x;
                                        temp2->next = temp3;
                                        temp3->next = temp1;
                                        temp2 = temp3;
                                    }
                                }
                                i++;
                                jhead=1;
                            }
                            else
                            {
                                temp2 = temp1;
                                temp1 = temp1->next;
                            }
                        }
                        else
                        {
                            temp2 = temp1;
                            temp1 = temp1->next;
                        }
                    }
                    if(jhead==0)  // compactage ....
                    {
                        if(x <= taille_total )
                        {
                            compactage();
                            temp1 = head;
                            temp2 = temp1;
                            while(temp1!=NULL && jhead==0)
                            {
                                if(temp1->type == 'L')
                                {
                                    if( x <= temp1->taille )
                                    {
                                        if(x == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = i;
                                            temp2 = temp1;
                                            temp1 = temp1->next;
                                        }
                                        else
                                        {
                                            temp3 = addhead();
                                            temp3->nbr = i;
                                            temp3->taille = x;
                                            temp1->taille -= x;
                                            temp2->next = temp3;
                                            temp3->next = temp1;
                                            temp2 = temp3;
                                        }
                                        jhead=1;
                                        i++;
                                    }
                                    else
                                    {
                                        temp2=temp1;
                                        temp1 = temp1->next;
                                    }
                                }
                                else
                                {
                                    temp2=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                        }
                    }
                }
                if(jhead==0) //  ajouter dans la fl ...
                {
                    temp1 = addfl();
                    temp1->taille = x;
                    temp1->nbr = i;
                    i++;
                }
            }
            else // si on a ( - )
            {
                printf("\t\t  On A -%dk\n\n",x);
                temp1 = head;
                jhead=0;
                int flp=0;
                while(temp1!=NULL && jhead==0)
                {
                    if( x == temp1->taille )
                    {
                        temp1->type = 'L';
                        jhead=1;
                    }
                    temp1 = temp1->next;
                }

                temp1 = fl;
                temp2 = temp1;
                while(temp1!=NULL && flp==0) // trouver le processus qu on va liberer dans FL
                {
                    if( x == temp1->taille )
                    {
                        if( temp2==temp1)
                        {
                            fl = temp1->next;
                            free(temp1);
                        }else
                        {
                            temp2->next = temp1->next;
                            free(temp1);
                        }
                        jhead=1;
                        flp=1;
                    }else
                    {
                        temp2 = temp1;
                        temp1 = temp1->next;
                    }
                }
            }

            jfl=0;
            jhead=0;
            while(jfl==0 && fl!=NULL)
            {

                jfl=1;
                temp1 = fl;
                temp2 = temp1;
                temp3 = temp1;
                temp4 = temp1;
                min = temp1->taille;

                while(temp1!=NULL) // SJF
                {
                    if(min > temp1->taille)
                    {
                        temp2 = temp1;
                        temp3 = temp4;
                        min   = temp1->taille;
                    }
                    temp4 = temp1;
                    temp1 = temp1->next;
                }

                temp1 = head;
                temp4 = temp1;
                jhead=0;
                taille_total=0;
                while(temp1!=NULL && jhead==0)
                {
                    if(temp1->type=='L')
                    {
                        taille_total += temp1->taille;
                        if(temp2->taille <= temp1->taille)
                        {
                            if(temp2==temp3) // fl to head ....
                            {
                                if(temp2->taille == temp1->taille)
                                {
                                    fl = temp2->next;
                                    temp1->type = 'O';
                                    temp1->nbr = temp2->nbr;
                                    free(temp2);
                                }
                                else
                                {
                                    if(temp1 == temp4)     //  si le bloc libre est le 1er bloc dans la liste head  ( la memoire )
                                    {
                                        fl = temp2->next;
                                        temp2->type = 'O';
                                        temp2->next = temp1;
                                        temp1->taille -= temp2->taille;
                                        head = temp2;
                                    }
                                    else                 //   si le bloc libre est au milieu dans la liste head  ( la memoire )
                                    {
                                        fl = temp2->next;
                                        temp2->type = 'O';
                                        temp2->next = temp1;
                                        temp1->taille -= temp2->taille;
                                        temp4->next = temp2;
                                    }
                                }
                            }
                            else  // si le processus est au milieu de la FL
                            {
                                if(temp2->taille == temp1->taille)   // si la taille du processus est la meme taille de la zone libre dans la liste head ( la memoire )
                                {
                                    temp3->next = temp2->next;
                                    temp1->type = 'O';
                                    temp1->nbr = temp2->nbr;
                                    free(temp2);
                                }
                                else
                                {
                                    if(temp1 == temp4)    //   si le bloc libre est le 1er bloc dans la liste head  ( la memoire )
                                    {
                                        temp3->next = temp2->next;
                                        temp2->type = 'O';
                                        temp2->next = temp1;
                                        temp1->taille -= temp2->taille;
                                        head = temp2;
                                    }
                                    else                  //   si le zone libre est au milieu dans la liste head  ( la memoire )
                                    {
                                        temp3->next = temp2->next;
                                        temp2->type = 'O';
                                        temp2->next = temp1;
                                        temp1->taille -= temp2->taille;
                                        temp4->next = temp2;
                                    }
                                }
                            }
                            jfl=0;
                            jhead=1;
                        }
                        else
                        {
                            temp4 = temp1;
                            temp1 = temp1->next;
                        }
                    }
                    else
                    {
                        temp4 = temp1;
                        temp1 = temp1->next;
                    }
                }
                if(jhead == 0)  // compactage ... pour fl
                {
                    if(temp2->taille <= taille_total )
                    {
                        compactage();
                        temp1 = head;
                        temp4 = temp1;
                        while(temp1!=NULL && jhead==0)
                        {
                            if(temp1->type == 'L')
                            {
                                if( temp2->taille <= temp1->taille )
                                {
                                    if(temp3==temp2)
                                    {
                                        fl = temp2->next;
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                    else
                                    {
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp3->next = temp2->next;
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                jhead=1;
                                }
                                else
                                {
                                    temp4=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                            else
                            {
                                temp4=temp1;
                                temp1 = temp1->next;
                            }
                        }
                    }
                }
            }
            afficher();
        }
    }
}


void WorstFit(FILE *p)
{
    node *temp1 , *temp2 , *temp3 , *temp4 , *temp5 , *temp6 ;
    int x , i , y , max , min , jpos , jhead , jfl , taille_total;
    char c,b,f;
    i=1;
    while(f != EOF)
    {
        fscanf(p,"%c%d%c",&c,&x,&b);
        f = fgetc(p);
        if(f != EOF)
        {
            if(c=='+') // si on a ( + )
            {
                printf("\t\t  On A %c%d%c\n\n",c,x,b);
                jhead=0;

                if(fl==NULL)
                {
                    temp1 = head;
                    temp2 = temp1;
                    temp3 = temp1;
                    temp4 = temp1;
                    jpos  = 0;
                    y = 0;
                    taille_total = 0 ;

                    while(temp1!=NULL && jpos==0) // pour trouver le meilleur bloc libre
                    {
                        if(temp1->type == 'L' )
                        {
                            taille_total += temp1->taille ;
                            if(x <= temp1->taille )
                            {
                                if(y==0)
                                {
                                    temp3 = temp1;
                                    temp4 = temp2;
                                    max = temp1->taille;
                                    y=1;
                                }
                                if(max < temp1->taille)
                                {
                                    temp3 = temp1;
                                    temp4 = temp2;
                                    max   = temp1->taille;
                                }
                            }
                        }
                        temp2 = temp1;
                        temp1 = temp1->next;
                    }
                    if( temp3->type=='L' )
                    {
                        if( x <= temp3->taille )
                        {
                            if(x == temp3->taille)
                            {
                                temp3->type = 'O';
                                temp3->nbr = i;
                            }
                            else
                            {
                                if(temp3==temp4)
                                {
                                    temp1 = addhead();
                                    temp1->nbr = i;
                                    temp1->taille = x;
                                    temp3->taille -= x;
                                    temp1->next = temp3;
                                    head = temp1;
                                }
                                else
                                {
                                    temp1 = addhead();
                                    temp1->nbr = i;
                                    temp1->taille = x;
                                    temp3->taille -= x;
                                    temp4->next = temp1;
                                    temp1->next = temp3;
                                }
                            }
                            i++;
                            jhead=1;
                        }
                    }

                    if(jhead==0)  // compactage ....
                    {
                        if(x <= taille_total )
                        {
                            compactage();
                            temp1 = head;
                            temp2 = temp1;
                            while(temp1!=NULL && jhead==0)
                            {
                                if(temp1->type == 'L')
                                {
                                    if( x <= temp1->taille )
                                    {
                                        if(x == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = i;
                                            temp2 = temp1;
                                            temp1 = temp1->next;
                                        }
                                        else
                                        {
                                            temp3 = addhead();
                                            temp3->nbr = i;
                                            temp3->taille = x;
                                            temp1->taille -= x;
                                            temp2->next = temp3;
                                            temp3->next = temp1;
                                            temp2 = temp3;
                                        }
                                        i++;
                                        jhead=1;
                                    }
                                    else
                                    {
                                        temp2=temp1;
                                        temp1 = temp1->next;
                                    }
                                }
                                else
                                {
                                    temp2=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                        }
                    }
                }
                if(jhead==0) // ajouter dans la fl ...
                {
                    temp1 = addfl();
                    temp1->taille = x;
                    temp1->nbr = i;
                    i++;
                }
                 //fl ...
            }
            else // si on a ( -> )
            {
                printf("\t\t  On A %c%d%c\n\n",c,x,b);
                temp1 = head;
                jhead=0;
                int flp=0;
                while(temp1!=NULL && jhead==0) // trouver la processus qu on va liberer dans HEAD
                {
                    if( x == temp1->taille )
                    {
                        temp1->type = 'L';
                        jhead=1;
                        flp=1;
                    }
                    temp1 = temp1->next;
                }

                temp1 = fl;
                temp2 = temp1;
                while(temp1!=NULL && flp==0) // trouver la processus qu on va liberer dans FL
                {
                    if( x == temp1->taille )
                    {
                        if( temp2==temp1)
                        {
                            fl = temp1->next;
                            free(temp1);
                        }else
                        {
                            temp2->next = temp1->next;
                            free(temp1);
                        }
                        jhead=1;
                        flp=1;
                    }else
                    {
                        temp2 = temp1;
                        temp1 = temp1->next;
                    }
                }

            }

            jfl=0;
            jhead=0;
            while(jfl==0 && fl!=NULL)
            {
                jfl=1;
                temp1 = fl;
                temp2 = temp1;
                temp3 = temp1;
                temp4 = temp1;
                min = temp1->taille;
                while(temp1!=NULL) // boocle SJF
                {
                    if(min > temp1->taille)
                    {
                        temp2 = temp1;
                        temp3 = temp4;
                        min   = temp1->taille;
                    }
                    temp4 = temp1;
                    temp1 = temp1->next;
                }

                temp1 = head;
                temp4 = temp1;
                temp5 = temp1;
                temp6 = temp1;
                jpos  = 0;
                y = 0;
                taille_total=0;
                while(temp5!=NULL && jpos==0)  //  pour trouver la meilleur zone libre
                {
                    if(temp5->type == 'L' )
                    {
                        taille_total += temp5->taille;
                        if(temp2->taille <= temp5->taille )
                        {
                            if(y==0)
                            {
                                temp1 = temp5;
                                temp4 = temp6;
                                max = temp1->taille;
                                y=1;
                            }
                            if(max < temp5->taille)
                            {
                                temp1 = temp5;
                                temp4 = temp6;
                                max   = temp5->taille;
                            }
                        }
                    }
                    temp6 = temp5;
                    temp5 = temp5->next;
                }

                jhead=0;

                if(temp1->type == 'L')
                {
                    if(temp2->taille <= temp1->taille)
                    {
                        if(temp2==temp3) //  fl to head ....
                        {
                            if(temp2->taille == temp1->taille)
                            {
                                fl = temp2->next;
                                temp1->type = 'O';
                                temp1->nbr = temp2->nbr;
                                free(temp2);
                            }
                            else
                            {
                                if(temp1 == temp4)    //   si le zone libre est le 1er bloc dans la liste head  ( la memoire )
                                {
                                    fl = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    head = temp2;
                                }
                                else                   //  si le zone libre est au milieu dans la liste head  ( la memoire )
                                {
                                    fl = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    temp4->next = temp2;
                                }
                            }
                        }
                        else //  si le processus est au milieu de la FL
                        {
                            if(temp2->taille == temp1->taille) //   si la taille du processus est la meme taille de la zone libre dans la liste head ( la memoire )
                            {
                                temp3->next = temp2->next;
                                temp1->type = 'O';
                                temp1->nbr = temp2->nbr;
                                free(temp2);
                            }
                            else
                            {
                                if(temp1 == temp4)    //   si le zone libre est le 1er bloc dans la liste head  ( la memoire )
                                {
                                    temp3->next = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    head = temp2;
                                }
                                else                   //  si le zone libre est au milieu dans la liste head  ( la memoire )
                                {
                                    temp3->next = temp2->next;
                                    temp2->type = 'O';
                                    temp2->next = temp1;
                                    temp1->taille -= temp2->taille;
                                    temp4->next = temp2;
                                }
                            }
                        }
                        jfl=0;
                        jhead=1;
                    }
                }
                if(jhead == 0)  // compactage ... pour fl
                {
                    if(temp2->taille <= taille_total )
                    {
                        compactage();
                        temp1 = head;
                        temp4 = temp1;
                        while(temp1!=NULL && jhead==0)
                        {
                            if(temp1->type == 'L')
                            {
                                if( temp2->taille <= temp1->taille )
                                {
                                    if(temp3==temp2)
                                    {
                                        fl = temp2->next;
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                    else
                                    {
                                        if(temp2->taille == temp1->taille)
                                        {
                                            temp1->type = 'O';
                                            temp1->nbr = temp2->nbr;
                                            free(temp2);
                                        }
                                        else
                                        {
                                            temp3->next = temp2->next;
                                            temp2->type = 'O';
                                            temp4->next = temp2;
                                            temp2->next = temp1;
                                            temp1->taille -= temp2->taille;
                                        }
                                    }
                                jhead=1;
                                }
                                else
                                {
                                    temp4=temp1;
                                    temp1 = temp1->next;
                                }
                            }
                            else
                            {
                                temp4=temp1;
                                temp1 = temp1->next;
                            }
                        }
                    }
                }
            }
            afficher();
        }
    }
}


int main()
{
    int i;
    node *p = (node*)malloc( sizeof(node) );
    FILE *pf = NULL;

    while(pf==NULL)
    {
        pf = fopen("tailleoriginal.txt","r");
    }


    printf("Entrer La Taille De La Memoire : ");
    scanf("%d",&p->taille);

    p->type   = 'L' ;
    p->next = NULL;
    head = p;

    do
    {
        printf(" 1 -> FirstFit \n 2 -> BestFit \n 3 -> WorstFit \n");
        printf("Entrer L'algorithme : " );
        scanf("%d",&i);
        printf("\n\n");
    }while(i<1 || i>3);

    switch(i)
    {
        case 1:
            printf(" ### Vous Avez Choisis FirstFit ### \n\n");
            FirstFit(pf);
            break;
        case 2:
            printf(" ### Vous Avez Choisis BestFit ### \n\n");
            BestFit(pf);
            break;
        case 3:
            printf(" ### Vous Avez Choisis WorstFit ### \n\n");
            WorstFit(pf);
            break;
    }
    return 0;
}
