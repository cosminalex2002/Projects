
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

extern int errno;
/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
    int sd;			// descriptorul de socket
    struct sockaddr_in server;	// structura folosita pentru conectare 
    char msg[100];		// mesajul trimis

    /* exista toate argumentele in linia de comanda? */
    if (argc != 3)
    {
        printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    /* stabilim portul */
    port = atoi (argv[2]);

    /* cream socketul */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("Eroare la socket().\n");
        return errno;
    }

    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(argv[1]);
    /* portul de conectare */
    server.sin_port = htons (port);
    
    /* ne conectam la server */
    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
        perror ("[client]Eroare la connect().\n");
        return errno;
    }

    bzero (msg, 100);
    fflush (stdout);

    if (read (sd, msg, 100) < 0)
    {
        perror ("Eroare la read() de la server.\n");
        return errno;
    }
    /*afisam mesajul primit */
    printf ("%s\n", msg);
    //sleep(5);
    /*sectiune logare*/

    int autentificare=0;
    do{       
        bzero (msg, 100);
        fflush (stdout);
        read (sd, msg, 100);
        printf ("%s", msg);/*Doriti sa va conectati ca administrator? y/n*/
        bzero (msg, 100);
        fflush (stdout);
        read(0,msg,100);
        if(strncmp(msg,"y",1)==0)//conectare ca administrator
        {   
            write(sd,msg,100); //trimitem y in server
            read(sd, msg,100); //citim Conectare ca admin   
            printf("\n%s\n\n", msg);
            read(sd, msg,100);//citim "Username admin"
            printf("%s", msg);
            bzero (msg, 100);
            fflush (stdout);
            read(0,msg,100);//citim username admin
            write(sd,msg,100);//trimitem username la server
            read(sd, msg,100);
            printf("%s", msg);//afisam "Parola administrator" :
            bzero (msg, 100);
            fflush (stdout);
            read(0,msg,100);//citim parola admin
            write(sd,msg,100);//trimitem parola la server
            read(sd, msg,100);//citim "conectat"
            printf("\n%s\n\n", msg);
            if(strncmp(msg,"Conectat ca administrator",25)==0)
            {          
                autentificare=1;
                int optiuni_admin=1;
                while(optiuni_admin==1)
                {
                    read(sd, msg,100);
                    printf("%s\n\n", msg);//afisam "optiuni administrator" 
                    read(sd, msg,100);
                    printf("%s\n", msg);
                    read(sd, msg,100);
                    printf("%s", msg);
                    bzero (msg, 100);
                    fflush (stdout);
                    read(0,msg,100);//citim optiunea
                    
                    write(sd,msg,100);//trimitem optiunea la server
                    if(strncmp(msg,"vizualizare campionate",22)==0)
                    {

                        read(sd, msg,100);
                        printf("\n%s\n\n", msg);//afisam In aceasta sectiune...
                        //sleep(3);
                        read(sd, msg,100);
                        printf("%s\n\n", msg);//afisam Campionatele sunt din sporturile..
                        read(sd, msg,100);
                        printf("%s", msg);//afisam Intrdoceti optiunea dorita 
                        bzero (msg, 100);
                        fflush (stdout);
                        read(0,msg,100);//citim optiunea
                        write(sd,msg,100);//trimitem optiunea la server
  
                        if(strncmp(msg,"tenis",5)==0)//vizualizare campionate tenis
                        {
                            read(sd, msg,100);
                            printf("%s\n\n", msg);//afisam Campionatele disponibile
                            do
                            {                                            
                                read(sd, msg,100);
                                if(strncmp(msg,"stop",4)==0)
                                {
                                    printf("\n");
                                    break;
                                }
                                printf("Nume campionat: %s  ", msg);
                                read(sd, msg,100);
                                printf("Stare campionat: %s  ", msg);
                                read(sd, msg,100);
                                printf("Numar maxim de jucatori: %s\n", msg);
                                do
                                {                                            
                                    read(sd, msg,100);
                                    if(strncmp(msg,"stop",4)==0)
                                    {
                                        printf("\n");
                                        break;
                                    }
                                    printf("Nume jucator: %s  ", msg);
                                    read(sd, msg,100);
                                    printf("Stare jucator: %s  \n", msg);                                   

                                } while (1); 
                                printf("\n");

                            } while (1);                          
                        }
                        else
                            if(strncmp(msg,"ping-pong",9)==0)//vizualizare camp ping
                            {
                                read(sd, msg,100);
                                printf("%s\n\n", msg);//afisam Campionatele disponibile
                                do
                                {                                            
                                    read(sd, msg,100);
                                    if(strncmp(msg,"stop",4)==0)
                                    {
                                        printf("\n");
                                        break;
                                    }
                                    printf("Nume campionat: %s  ", msg);
                                    read(sd, msg,100);
                                    printf("Stare campionat: %s  ", msg);
                                    read(sd, msg,100);
                                    printf("Numar maxim de jucatori: %s\n", msg);
                                    do
                                    {                                            
                                        read(sd, msg,100);
                                        if(strncmp(msg,"stop",4)==0)
                                        {
                                            printf("\n");
                                            break;
                                        }
                                        printf("Nume jucator: %s  ", msg);
                                        read(sd, msg,100);
                                        printf("Stare jucator: %s  \n", msg);                                   

                                    } while (1); 
                                    printf("\n");

                                } while (1);
                            }
                            else
                                if(strncmp(msg,"fotbal",6)==0)
                                {
                                    read(sd, msg,100);
                                    printf("%s\n\n", msg);//afisam Campionatele disponibile
                                    do
                                    {                                            
                                        read(sd, msg,100);
                                        if(strncmp(msg,"stop",4)==0)
                                        {
                                            printf("\n");
                                            break;
                                        }
                                        printf("Nume campionat: %s  ", msg);
                                        read(sd, msg,100);
                                        printf("Stare campionat: %s  ", msg);

                                        printf("Numar maxim de echipe: 3\n");
                                        do
                                        {                                            
                                            read(sd, msg,100);
                                            if(strncmp(msg,"stop",4)==0)
                                            {
                                                printf("\n");
                                                break;
                                            }
                                            printf("Nume echipa: %s  ", msg);
                                            read(sd, msg,100);
                                            printf("Stare echipa: %s  ", msg); 
                                            read(sd, msg,100);
                                            printf("Puncte echipa: %s \n", msg);                                  

                                        } while (1); 
                                        printf("\n");
                                    } while (1);  
                                }

                        
           
                    }
                    else
                        if(strncmp(msg,"inregistrare campionat nou",26)==0)
                        {
                            read(sd, msg,100);
                            printf("\n%s", msg);//tipuri de sport
                            read(sd, msg,100);
                            printf("\n%s", msg);//ce tip de sport alegeti
                            bzero (msg, 100);
                            fflush (stdout);
                            read(0,msg,100);//citim sportul
                            //s a citit tenis
                            write(sd,msg,100);//trimitem sportul ales
                            if(strncmp(msg,"tenis",5)==0||strncmp(msg,"ping-pong",9)==0)
                            {    
                                read(sd, msg,100);
                                printf("\n%s", msg);//indocueti nr de jucatori
                                bzero (msg, 100);
                                fflush (stdout);
                                read(0,msg,100);//citim nr de jucatori
                                write(sd,msg,100);//trimitem nr de jucatori la server
                                read(sd, msg,100);//citim "numele campionatului";
                                printf("\n%s", msg);
                                bzero (msg, 100);
                                fflush (stdout);
                                read(0,msg,100);//citim numele camp
                                write(sd,msg,100);//trimitem numele la server
                                read(sd, msg,100);//citim "inregistrare cu succes";
                                printf("\n%s\n", msg);
                            }
                            else
                                if(strncmp(msg,"fotbal",6)==0)
                                {
                                    read(sd, msg,100);//citim "numele campionatului";
                                    printf("\n%s", msg);
                                    bzero (msg, 100);
                                    fflush (stdout);
                                    read(0,msg,100);//citim numele camp
                                    write(sd,msg,100);//trimitem numele la server
                                    read(sd, msg,100);//citim "inregistrare cu succes";
                                    printf("\n%s\n", msg);
                                }
                        }
                        else
                            if(strncmp(msg,"simulare campionat",18)==0)
                            {
                                read(sd, msg,100);
                                printf("\n%s\n\n", msg);//afisam In aceasta sectiune...
                                //sleep(3);
                                read(sd, msg,100);
                                printf("%s\n\n", msg);//afisam Campionatele sunt din sporturile..
                                read(sd, msg,100);
                                printf("%s", msg);//afisam Intrdoceti optiunea dorita 
                                bzero (msg, 100);
                                fflush (stdout);
                                read(0,msg,100);//citim optiunea
                                write(sd,msg,100);//trimitem optiunea la server
                                if(strncmp(msg,"fotbal",6)==0)
                                {
                                    read(sd, msg,100);
                                    printf("%s\n\n", msg);//afisam Campionatele disponibile
                                    do
                                    {                                            
                                        read(sd, msg,100);
                                        if(strncmp(msg,"stop",4)==0)
                                        {
                                            printf("\n");
                                            break;
                                        }
                                        printf("Nume campionat: %s  ", msg);
                                        read(sd, msg,100);
                                        printf("Stare campionat: %s  ", msg);                                      
                                        printf("Numar maxim de echipe: 3\n");
                                    } while (1); 
                                    read(sd, msg,100);
                                    printf("%s", msg);//afisam Intrdoceti optiunea dorita 
                                    bzero (msg, 100);
                                    fflush (stdout);
                                    read(0,msg,100);//citim optiunea de campionat
                                    write(sd,msg,100);//trimitem optiunea la server

                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    //sleep(3);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    //sleep(3);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    //sleep(3);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    //afisam castigatoarea
                                    read(sd, msg,100);
                                    printf("%s", msg);
                                    read(sd, msg,100);
                                   // sleep(3);
                                    printf("%s!!\n\n", msg);
                                }
                            }
                            else
                                if(strncmp(msg,"inchidere conexiune",19)==0)
                                {                               
                                    optiuni_admin=0;
                                }
                           
                }
            }
            else
            {
                autentificare=0;
            }
        }   
        else 
            if(strncmp(msg,"n",1)==0)//conectare ca utilizator
            {
                write(sd,msg,100); //trimitem y in server
                read(sd, msg,100); //citim Conectare ca util   
                printf("\n%s\n", msg);

                read(sd, msg,100); //citim Conectare ca util   
                printf("%s", msg);
                bzero (msg, 100);
                fflush (stdout);
                read(0,msg,100);//cititm daca are cont
                write(sd,msg,100);//trimitem raspunsul daca are cont de util sau nu 
                if(strncmp(msg,"y",1)==0)//utilizatorul are cont
                {
                    read(sd, msg,100);//citim "Username util"
                    printf("%s", msg);
                    bzero (msg, 100);
                    fflush (stdout);
                    read(0,msg,100);//citim username util
                    write(sd,msg,100);//trimitem username la server
                    read(sd, msg,100);
                    printf("%s", msg);//afisam "Parola util" :
                    bzero (msg, 100);
                    fflush (stdout);
                    read(0,msg,100);//citim parola util
                    write(sd,msg,100);//trimitem parola la server
                    read(sd, msg,100);//citim "conectat" ca util
                    
                    printf("\n%s\n\n", msg);//afisam CONECTAT CA UTIL
                    if(strncmp(msg,"Conectat ca utilizator",22)==0)
                    {          
                        autentificare=1;   
                        int optiuni_util=1;
                        while(optiuni_util==1)
                        {
                            read(sd,msg,100);
                            printf("%s\n\n",msg);
                            read(sd,msg,100);
                            printf("%s\n",msg);
                            read(sd, msg,100);
                            printf("%s", msg);
                            bzero (msg, 100);
                            fflush (stdout);
                            read(0,msg,100);//citim optiunea                          
                            write(sd,msg,100);//trimitem optiunea la server

                            if(strncmp(msg,"vizualizare campionate",22)==0)
                            {
                                //printf("ok1");
                                read(sd, msg,100);
                                printf("\n%s\n\n", msg);//afisam In aceasta sectiune...
                                //sleep(3);
                                read(sd, msg,100);
                                printf("%s\n\n", msg);//afisam Campionatele sunt din sporturile..
                                read(sd, msg,100);
                                printf("%s", msg);//afisam Intrdoceti optiunea dorita 
                                bzero (msg, 100);
                                fflush (stdout);
                                read(0,msg,100);//citim optiunea
                                write(sd,msg,100);//trimitem optiunea la server

                                if(strncmp(msg,"ping-pong",9)==0)
                                {
                                    read(sd, msg,100);
                                    printf("%s\n\n", msg);//afisam Campionatele disponibile
                                    do
                                    {                                            
                                        read(sd, msg,100);
                                        if(strncmp(msg,"stop",4)==0)
                                        {
                                            printf("\n");
                                            break;
                                        }
                                        printf("Nume campionat: %s  ", msg);
                                        read(sd, msg,100);
                                        printf("Stare campionat: %s  ", msg);
                                        read(sd, msg,100);
                                        printf("Numar maxim de jucatori: %s\n", msg);
                                        do
                                        {                                            
                                            read(sd, msg,100);
                                            if(strncmp(msg,"stop",4)==0)
                                            {
                                                printf("\n");
                                                break;
                                            }
                                            printf("Nume jucator: %s ", msg);
                                            read(sd, msg,100);
                                            printf("Stare jucator: %s \n", msg);                                   

                                        } while (1); 
                                        printf("\n");

                                    } while (1);
                                }
                                else
                                    if(strncmp(msg,"tenis",5)==0)
                                    {
                                        read(sd, msg,100);
                                        printf("%s\n\n", msg);//afisam Campionatele disponibile
                                        do
                                        {                                            
                                            read(sd, msg,100);
                                            if(strncmp(msg,"stop",4)==0)
                                            {
                                                printf("\n");
                                                break;
                                            }
                                            printf("Nume campionat: %s  ", msg);
                                            read(sd, msg,100);
                                            printf("Stare campionat: %s  ", msg);
                                            read(sd, msg,100);
                                            printf("Numar maxim de jucatori: %s\n", msg);
                                            do
                                            {                                            
                                                read(sd, msg,100);
                                                if(strncmp(msg,"stop",4)==0)
                                                {
                                                    printf("\n");
                                                    break;
                                                }
                                                printf("Nume jucator: %s ", msg);
                                                read(sd, msg,100);
                                                printf("Stare jucator: %s \n", msg);                                   

                                            } while (1); 
                                            printf("\n");
                                        } while (1);   
                                    }
                                    else
                                        if(strncmp(msg,"fotbal",6)==0)
                                        {
                                            read(sd, msg,100);
                                            printf("%s\n\n", msg);//afisam Campionatele disponibile
                                            do
                                            {                                            
                                                read(sd, msg,100);
                                                if(strncmp(msg,"stop",4)==0)
                                                {
                                                    printf("\n");
                                                    break;
                                                }
                                                printf("Nume campionat: %s  ", msg);
                                                read(sd, msg,100);
                                                printf("Stare campionat: %s  ", msg);

                                                printf("Numar maxim de echipe: 3\n");
                                                do
                                                {                                            
                                                    read(sd, msg,100);
                                                    if(strncmp(msg,"stop",4)==0)
                                                    {
                                                        printf("\n");
                                                        break;
                                                    }
                                                    printf("Nume echipa: %s  ", msg);
                                                    read(sd, msg,100);
                                                    printf("Stare echipa: %s  ", msg); 
                                                    read(sd, msg,100);
                                                    printf("Puncte echipa: %s \n", msg);                                  

                                                } while (1); 
                                                printf("\n");
                                            } while (1);  
                                        }
                            }
                            else
                                if(strncmp(msg,"inscriere",9)==0)
                                {                                  
                                    read(sd, msg,100);
                                    printf("%s\n", msg);//afisam Campionatele sunt din sporturile..
                                    read(sd, msg,100);
                                    printf("%s", msg);//afisam Intrdoceti optiunea dorita 
                                    bzero (msg, 100);
                                    fflush (stdout);
                                    read(0,msg,100);//citim optiunea
                                    write(sd,msg,100);//trimitem optiunea la server
                                    if(strncmp(msg,"tenis",5)==0)
                                    {
                                        read(sd, msg,100);
                                        printf("%s", msg);
                                        read(sd, msg,100);
                                        //sleep(2);
                                        printf("%s", msg);
                                        // sleep(2);
                                        read(sd, msg,100);
                                        printf("%s", msg);
                                        //sleep(2);
                                        read(sd, msg,100);
                                        printf("%s", msg);
                                        //sleep(2);
                                        read(sd, msg,100);
                                        printf("%s", msg);
                                        //sleep(2);
                                        read(sd, msg,100);
                                        printf("%s\n", msg);//campionate disponibile                                       
                                        do
                                        {                                            
                                            read(sd, msg,100);
                                            if(strncmp(msg,"stop",4)==0)
                                            {
                                                printf("\n");
                                                break;
                                            }
                                            printf("Nume campionat: %s  ", msg);
                                            read(sd, msg,100);
                                            printf("Stare campionat: %s  ", msg);
                                            read(sd, msg,100);
                                            printf("Numar maxim de jucatori: %s\n", msg);

                                        } while (1);

                                        read(sd, msg,100);
                                        printf("%s", msg);
                                        bzero (msg, 100);
                                        fflush (stdout);
                                        read(0,msg,100);//citim numele campionatului la care se isncrie utilizatorul
                                        write(sd,msg,100);//trimitem optiunea la server
                                        read(sd, msg,100);
                                        printf("%s", msg);//scriem INtroduceti numele participantului
                                        bzero (msg, 100);
                                        fflush (stdout);
                                        read(0,msg,100);//citim numele participantului
                                        write(sd,msg,100);//trimitem numele la server
                                        read(sd, msg,100);
                                        printf("%s", msg);//scriem Jucator inregistrat cu succes
                                    }
                                    else
                                        if(strncmp(msg,"fotbal",6)==0)
                                        {
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            read(sd, msg,100);
                                            //sleep(2);
                                            printf("%s", msg);
                                            // sleep(2);
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            //sleep(2);
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            //sleep(2);
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            //sleep(2);
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            //sleep(2);
                                            read(sd, msg,100);
                                            printf("%s", msg);//campionate disponibile
                                            do
                                            {                                            
                                                read(sd, msg,100);
                                                if(strncmp(msg,"stop",4)==0)
                                                {
                                                    printf("\n");
                                                    break;
                                                }
                                                printf("Nume campionat: %s  ", msg);
                                                read(sd, msg,100);
                                                printf("Stare campionat: %s  ", msg);
                                                printf("Numar maxim de echipe: 3\n");

                                            } while (1);
                                            read(sd, msg,100);
                                            printf("%s", msg);
                                            bzero (msg, 100);
                                            fflush (stdout);
                                            read(0,msg,100);//citim numele campionatului la care se isncrie utilizatorul
                                            write(sd,msg,100);//trimitem optiunea la server
                                            read(sd, msg,100);
                                            printf("%s", msg);//scriem INtroduceti numele participantului
                                            bzero (msg, 100);
                                            fflush (stdout);
                                            read(0,msg,100);//citim numele participantului
                                            write(sd,msg,100);//trimitem numele la server
                                            read(sd, msg,100);
                                            printf("%s", msg);//scriem Jucator inregistrat cu succes
                                        }
                                        else
                                            if(strncmp(msg,"ping-pong",9)==0)
                                            {
                                                read(sd, msg,100);
                                                printf("%s", msg);
                                                read(sd, msg,100);
                                                //sleep(2);
                                                printf("%s", msg);
                                                // sleep(2);
                                                read(sd, msg,100);
                                                printf("%s", msg);
                                                //sleep(2);
                                                read(sd, msg,100);
                                                printf("%s", msg);
                                                //sleep(2);
                                                read(sd, msg,100);
                                                printf("%s", msg);
                                                //sleep(2);
                                                read(sd, msg,100);
                                                printf("%s\n", msg);//campionate disponibile
                                                
                                                do
                                                {                                            
                                                    read(sd, msg,100);
                                                    if(strncmp(msg,"stop",4)==0)
                                                    {
                                                        printf("\n");
                                                        break;
                                                    }
                                                    printf("Nume campionat: %s  ", msg);
                                                    read(sd, msg,100);
                                                    printf("Stare campionat: %s  ", msg);
                                                    read(sd, msg,100);
                                                    printf("Numar maxim de jucatori: %s\n", msg);

                                                } while (1);

                                                read(sd, msg,100);
                                                printf("%s", msg);
                                                bzero (msg, 100);
                                                fflush (stdout);
                                                read(0,msg,100);//citim numele campionatului la care se isncrie utilizatorul
                                                write(sd,msg,100);//trimitem optiunea la server
                                                read(sd, msg,100);
                                                printf("%s", msg);//scriem INtroduceti numele participantului
                                                bzero (msg, 100);
                                                fflush (stdout);
                                                read(0,msg,100);//citim numele participantului
                                                write(sd,msg,100);//trimitem numele la server
                                                read(sd, msg,100);
                                                printf("%s", msg);//scriem Jucator inregistrat cu succes
                                            }
                                }
                                else
                                    if(strncmp(msg,"inchidere conexiune",19)==0)
                                    {
                                        
                                        optiuni_util=0;
                                    }
                        }                       
                    }
                    else
                    {
                        autentificare=0;
                    }
                }
                else//utilizatorul nu are cont=> inregistrare
                {
                    read(sd, msg,100);
                    printf("%s", msg);//Inregistrare util nou..
                    read(sd, msg,100);
                    printf("%s", msg);//username util nou
                    bzero (msg, 100);
                    fflush (stdout);
                    read(0,msg,100);//citim username util nou
                    write(sd, msg,100);//trimitem la server user

                    read(sd, msg,100);
                    printf("%s", msg);//parola util nou
                    bzero (msg, 100);
                    fflush (stdout);
                    read(0,msg,100);//citim parola util nou
                    write(sd, msg,100);//trimitem la server parola

                    read(sd, msg,100);
                    
                    printf("%s \n", msg);//util inregistrat cu succes
                    //sleep(3);
                    read(sd, msg,100);
                    printf("%s \n", msg);//Inapoi la sectiunea de logare..
                    //sleep(3);

                }
            }
        } while( autentificare == 0 );
    close (sd);
}