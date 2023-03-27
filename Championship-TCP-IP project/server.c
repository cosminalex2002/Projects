
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> 
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <time.h>
#define PORT 2021


extern int errno;
static int callback(void *data, int count, char **informatie, char **coloane)
{
	int idx;
	for (idx = 0; idx < count; idx++) 
	{	
		printf("Nume echipa: %s     ", informatie[idx]);
	}
	return 0;
}
int main ()
{	
	srand ( time(NULL) );
	 
	//creare baze de date 
	sqlite3 *db;
   	char *zErrMsg = 0;
   	int rc;
   	char *sql;
   	const char* data = "Callback function called";
	rc = sqlite3_open("test.db", &db);
	char *messaggeError;
    struct sockaddr_in server;	// structura folosita de server
    struct sockaddr_in from;
    char msg[100];		//mesajul primit de la client
    char msgrasp[100]=" ";        //mesaj de raspuns pentru client
    int sd;			//descriptorul de socket

    /* crearea unui socket */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
    	perror ("[server]Eroare la socket().\n");
    	return errno;
    }

    /* pregatirea structurilor de date */
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));

    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;
    /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    /* utilizam un port utilizator */
    server.sin_port = htons (PORT);

    /* atasam socketul */
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
    	perror ("[server]Eroare la bind().\n");
    	return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen (sd, 1) == -1)
    {
    	perror ("[server]Eroare la listen().\n");
    	return errno;
    }
    /* servim in mod concurent clientii... */

	int conectat=0;
    while (1)
    {
    	int client;
    	int length = sizeof (from);
		if(conectat==0)
		{
    		printf ("[server]Asteptam la portul %d...\n",PORT);
    		fflush (stdout);
			conectat=1;
		}
    	/* acceptam un client (stare blocanta pina la realizarea conexiunii) */
    	client = accept (sd, (struct sockaddr *) &from, &length);

    	/* eroare la acceptarea conexiunii de la un client */
    	if (client < 0)
    	{
    		perror ("[server]Eroare la accept().\n");
    		continue;
    	}

    	int pid;
    	if ((pid = fork()) == -1) {
    		close(client);
    		continue;
    	} else if (pid > 0) {
    		close(client);
    		while(waitpid(-1,NULL,WNOHANG));
    		continue;
    	} 
		else 
			if (pid == 0) 
			{
    			close(sd);
				bzero(msgrasp,100);
				strcpy(msgrasp,"Bine ati venit pe Championship! Aici puteti urmari ultimele nautati din sport.\n\n");

				if (write (client, msgrasp, 100) <= 0)
    			{
    				perror ("[server]Eroare la write() catre client.\n");
    				continue;		
    			} 

				int user_cu_parola=0;
				do{ 

					int user_cu_parola=0;
					strcpy(msgrasp,"Doriti sa va conectati ca administrator? [y/n] : ");
					write (client, msgrasp, 100);
					read (client, msg, 100);
					if(strncmp(msg,"y",1)==0)/*logare ca administrator*/
					{						
						strcpy(msgrasp,"Conectare ca administrator...");
						write (client, msgrasp, 100);					
						
						strcpy(msgrasp,"Username administrator: ");
						write (client, msgrasp, 100);
						read (client, msg, 100);//citim username
						//verificam username in baza de date					
						msg[strlen(msg)-1]='\0';
						sqlite3_stmt *res1;
						char sql2[1000];
						sprintf(sql2,"select * from ADMINISTRATORI where USERNAME like '%s'",msg);
						rc = sqlite3_prepare_v2(db, sql2, -1, &res1, NULL);
						int step=sqlite3_step(res1);						
						if(step != SQLITE_DONE)
						{
							user_cu_parola++;
						}
						sqlite3_finalize(res1);

						strcpy(msgrasp,"Parola administrator: ");
						write (client, msgrasp, 100);
						read (client, msg, 100);//citim parola
						//verificam parola
						msg[strlen(msg)-1]='\0';				
						sqlite3_stmt *res2;						
						sprintf(sql2,"select * from ADMINISTRATORI where PAROLA like '%s'",msg);
						rc = sqlite3_prepare_v2(db, sql2, -1, &res2, NULL);
						int step2=sqlite3_step(res2);
						if(step2 != SQLITE_DONE)
						{
							user_cu_parola++;				
						}			
						sqlite3_finalize(res2);
						if(user_cu_parola==2)
						{
							strcpy(msgrasp,"Conectat ca administrator");
							write (client, msgrasp, 100);//scriem conectat
							int optiuni_admin=1;							
							while( optiuni_admin==1)
							{
								strcpy(msgrasp,"OPTIUNI ADMINISTRATOR:");
								write (client, msgrasp, 100);//
								strcpy(msgrasp," -vizualizare campionate\n -simulare campionat\n -inregistrare campionat nou\n -inchidere conexiune\n");
								write (client, msgrasp, 100);
								strcpy(msgrasp,"Introduceti optiunea dorita: ");
								write (client, msgrasp, 100);
								read (client, msg, 100);//citim optiunea
								if(strncmp(msg,"vizualizare campionate",22)==0)
								{
									
									strcpy(msgrasp,"In aceasta sectiune puteti urmari situatia ultimelor campionate");
									write (client, msgrasp, 100);
									strcpy(msgrasp,"Campionatele fac parte din urmatoarele sporturi:\n\n  -fotbal\n  -tenis\n  -ping-pong");
									write (client, msgrasp, 100);
									strcpy(msgrasp,"Introduceti optiunea dorita: ");
									write (client, msgrasp, 100);
									read (client, msg, 100);//citim sportul ales
									if(strncmp(msg,"tenis",5)==0)
									{										
										strcpy(msgrasp,"Campionate de tenis disponibile:");
										write (client, msgrasp, 100);

										sqlite3_stmt *nume_tabele;
										sqlite3_stmt *stare_campionat;
										sqlite3_stmt *numarul;

										char y[700];
										char y1[700];
										char y2[700];
										sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_TENIS ;", -1, &stare_campionat, NULL);
										sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_TENIS ;", -1, &numarul, NULL);
										sqlite3_prepare(db, "SELECT NUME FROM TABELE_TENIS ;", -1, &nume_tabele, NULL);
										while (sqlite3_step(nume_tabele) == SQLITE_ROW && sqlite3_step(stare_campionat) == SQLITE_ROW && sqlite3_step(numarul) == SQLITE_ROW)
										{
											strcpy(y,(char*)sqlite3_column_text(nume_tabele, 0));
											strcpy(msgrasp,y);
											write (client, msgrasp, 100);
											strcpy(y1,(char*)sqlite3_column_text(stare_campionat, 0));
											strcpy(msgrasp,y1);
											write (client, msgrasp, 100);
											strcpy(y2,(char*)sqlite3_column_text(numarul, 0));
											strcpy(msgrasp,y2);
											write (client, msgrasp, 100);
											//afisam jucatorii

											sqlite3_stmt *Nume;
											sqlite3_stmt *stare_jucator;
											char test1[1000],test2[1000],test3[1000],test4[1000];
											sprintf(test1,"select NUME from %s;",y);
											sprintf(test2,"select STARE_JUCATOR from %s;",y);
											sqlite3_prepare(db, test1, -1, &Nume, NULL);
											sqlite3_prepare(db, test2, -1, &stare_jucator, NULL);
											while (sqlite3_step(Nume) == SQLITE_ROW && sqlite3_step(stare_jucator) == SQLITE_ROW)
											{
												strcpy(test3,(char*)sqlite3_column_text(Nume, 0));
												strcpy(msgrasp,test3);
												write (client, msgrasp, 100);
												strcpy(test4,(char*)sqlite3_column_text(stare_jucator, 0));
												strcpy(msgrasp,test4);
												write (client, msgrasp, 100);
											}
											sqlite3_finalize(Nume);
											sqlite3_finalize(stare_jucator);
											strcpy(msgrasp,"stop");
										   	write (client, msgrasp, 100);	
										}
										strcpy(msgrasp,"stop");
										write (client, msgrasp, 100);
										sqlite3_finalize(nume_tabele);
										sqlite3_finalize(stare_campionat);
										sqlite3_finalize(numarul);
									}
									else
										if(strncmp(msg,"fotbal",6)==0)
										{
											strcpy(msgrasp,"Campionate de fotbal disponibile:");
											write (client, msgrasp, 100);
											sqlite3_stmt *nume_fot;
											sqlite3_stmt *stare_fot;
											char l[700];
											char l1[700];
											sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_FOTBAL;", -1, &stare_fot, NULL);
											sqlite3_prepare(db, "SELECT NUME FROM TABELE_FOTBAL ;", -1, &nume_fot, NULL);
											while (sqlite3_step(nume_fot) == SQLITE_ROW && sqlite3_step(stare_fot) == SQLITE_ROW )
											{
												strcpy(l,(char*)sqlite3_column_text(nume_fot, 0));
												strcpy(msgrasp,l);
												write (client, msgrasp, 100);
												strcpy(l1,(char*)sqlite3_column_text(stare_fot, 0));
												strcpy(msgrasp,l1);
												write (client, msgrasp, 100);
											
												//afisam echipele

												sqlite3_stmt *Nume3_fot;
												sqlite3_stmt *stare_echipa_fot;
												sqlite3_stmt *puncte_fot;

												char test1[1000],test2[1000],test3[1000],test4[1000],test5[1000],test6[1000];
												sprintf(test1,"select NUME from %s;",l);
												sprintf(test2,"select STARE_JUCATOR from %s;",l);
												sprintf(test3,"select PUNCTE from %s;",l);
												sqlite3_prepare(db, test1, -1, &Nume3_fot, NULL);
												sqlite3_prepare(db, test2, -1, &stare_echipa_fot, NULL);
												sqlite3_prepare(db, test3, -1, &puncte_fot, NULL);
												
												while (sqlite3_step(Nume3_fot) == SQLITE_ROW && sqlite3_step(stare_echipa_fot) == SQLITE_ROW && sqlite3_step(puncte_fot) == SQLITE_ROW)
												{
													
													strcpy(test4,(char*)sqlite3_column_text(Nume3_fot, 0));
													strcpy(msgrasp,test4);
													write (client, msgrasp, 100);
													strcpy(test5,(char*)sqlite3_column_text(stare_echipa_fot, 0));
													strcpy(msgrasp,test5);
													write (client, msgrasp, 100);
													strcpy(test6,(char*)sqlite3_column_blob(puncte_fot, 0));						
													strcpy(msgrasp,test6);
													write (client, msgrasp, 100);
													
												}
												sqlite3_finalize(Nume3_fot);
												sqlite3_finalize(stare_echipa_fot);
												sqlite3_finalize(puncte_fot);
												strcpy(msgrasp,"stop");
												write (client, msgrasp, 100);
												
											}
											strcpy(msgrasp,"stop");
											write (client, msgrasp, 100);
											sqlite3_finalize(nume_fot);
											sqlite3_finalize(stare_fot);
										}
										else
											if(strncmp(msg,"ping-pong",9)==0)
											{
										
												strcpy(msgrasp,"Campionate de ping-pong disponibile:");
												write (client, msgrasp, 100);

												sqlite3_stmt *nume_tabele;
												sqlite3_stmt *stare_campionat;
												sqlite3_stmt *numarul;

												char u[700];
												char u1[700];
												char u2[1000];
												sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_PING ;", -1, &stare_campionat, NULL);
												sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_PING ;", -1, &numarul, NULL);
												sqlite3_prepare(db, "SELECT NUME FROM TABELE_PING ;", -1, &nume_tabele, NULL);
												while (sqlite3_step(nume_tabele) == SQLITE_ROW && sqlite3_step(stare_campionat) == SQLITE_ROW && sqlite3_step(numarul) == SQLITE_ROW)
												{
													strcpy(u,(char*)sqlite3_column_text(nume_tabele, 0));
													strcpy(msgrasp,u);
													write (client, msgrasp, 100);
													strcpy(u1,(char*)sqlite3_column_text(stare_campionat, 0));
													strcpy(msgrasp,u1);
													write (client, msgrasp, 100);
													strcpy(u2,(char*)sqlite3_column_text(numarul, 0));
													strcpy(msgrasp,u2);
													write (client, msgrasp, 100);
													//afisam jucatorii


													sqlite3_stmt *Nume;
													sqlite3_stmt *stare_jucator;
													char test1[1000],test2[1000],test3[1000],test4[1000];
													sprintf(test1,"select NUME from %s;",u);
													sprintf(test2,"select STARE_JUCATOR from %s;",u);
													sqlite3_prepare(db, test1, -1, &Nume, NULL);
													sqlite3_prepare(db, test2, -1, &stare_jucator, NULL);
													while (sqlite3_step(Nume) == SQLITE_ROW && sqlite3_step(stare_jucator) == SQLITE_ROW)
													{
														strcpy(test3,(char*)sqlite3_column_text(Nume, 0));
														strcpy(msgrasp,test3);
														write (client, msgrasp, 100);
														strcpy(test4,(char*)sqlite3_column_text(stare_jucator, 0));
														strcpy(msgrasp,test4);
														write (client, msgrasp, 100);
												
													}
													sqlite3_finalize(Nume);
													sqlite3_finalize(stare_jucator);
													strcpy(msgrasp,"stop");
													write (client, msgrasp, 100);
													
												}
												strcpy(msgrasp,"stop");
												write (client, msgrasp, 100);
												sqlite3_finalize(nume_tabele);
												sqlite3_finalize(stare_campionat);
												sqlite3_finalize(numarul);
											}

								}
								else
									if(strncmp(msg,"inregistrare campionat nou",26)==0)
									{
										strcpy(msgrasp,"Sporturi:\n\n  -fotbal\n  -tenis\n  -ping-pong\n\n");
										write (client, msgrasp, 100);
										strcpy(msgrasp,"Tipul de sport ales: ");
										write (client, msgrasp, 100);
										read (client, msg, 100);//citim sportul
										if(strncmp(msg,"tenis",5)==0)//optiuni tenis
										{

											strcpy(msgrasp,"Introduceti numarul de jucatori (4 sau 8): ");
											write (client, msgrasp, 100);
											read (client, msg, 100);//citim nr de jucatori
											int nr_juc;
											msg[strlen(msg)-1]='\0';
											nr_juc=atoi(msg);											
											strcpy(msgrasp,"Numele campionatului: ");
											write(client,msgrasp,100);
											read(client,msg,100);
											msg[strlen(msg)-1]='\0';
											char mac[1000];
											sprintf (mac,"INSERT INTO TABELE_TENIS (NUME, STARE_CAMPIONAT, NR_JUCATORI) VALUES ('%s','INCHIS', %d);",msg,nr_juc);
											rc = sqlite3_exec(db, mac, callback, 0, &zErrMsg);										
											char tenis[1000];
											sprintf(tenis,"CREATE TABLE %s (" \
													"NUME       	 TEXT    ,"\
													"STARE_JUCATOR   TEXT	  );",msg);																	
											rc = sqlite3_exec(db, tenis, callback, 0, &zErrMsg);
											strcpy(msgrasp,"Campionat inregistrat cu succes!");
											write(client,msgrasp,100);
														
										}
										else
											if(strncmp(msg,"ping-pong",9)==0)
											{
												strcpy(msgrasp,"Introduceti numarul de jucatori (4 sau 8): ");
												write (client, msgrasp, 100);
												read (client, msg, 100);//citim nr de jucatori
												msg[strlen(msg)-1]='\0';
												int nr_juc1;
												nr_juc1=atoi(msg);																							
												strcpy(msgrasp,"Numele campionatului: ");
												write(client,msgrasp,100);
												read(client,msg,100);
												msg[strlen(msg)-1]='\0';
												char mac1[1000];
												sprintf (mac1,"INSERT INTO TABELE_PING(NUME,STARE_CAMPIONAT,NR_JUCATORI) VALUES ('%s','INCHIS',%d);",msg,nr_juc1);
												rc = sqlite3_exec(db, mac1, callback, 0, &zErrMsg);										
												char ping[1000];
												sprintf(ping,"CREATE TABLE %s (" \
														"NUME       	 TEXT    ,"\
														"STARE_JUCATOR   TEXT	  );",msg);																	
												rc = sqlite3_exec(db, ping, callback, 0, &zErrMsg);
												strcpy(msgrasp,"Campionat inregistrat cu succes!");
												write(client,msgrasp,100);	
											}
											else
												if(strncmp(msg,"fotbal",6)==0)
												{																															
													strcpy(msgrasp,"Numele campionatului: ");
													write(client,msgrasp,100);
													read(client,msg,100);
													msg[strlen(msg)-1]='\0';
													char mac8[1000];
													sprintf (mac8,"INSERT INTO TABELE_FOTBAL(NUME,STARE_CAMPIONAT) VALUES ('%s','INCHIS');",msg);
													rc = sqlite3_exec(db, mac8, callback, 0, &zErrMsg);										
													char pin[1000];
													sprintf(pin,"CREATE TABLE %s("\
															"NUME TEXT ,"\
															"PUNCTE INTEGER ,"\
															"STARE_JUCATOR TEXT );",msg);																	
													rc = sqlite3_exec(db, pin, callback, 0, &zErrMsg);
													strcpy(msgrasp,"Campionat inregistrat cu succes!");
													write(client,msgrasp,100);	
												}										
									}
									else
										if(strncmp(msg,"simulare campionat",18)==0)
										{
											strcpy(msgrasp,"In aceasta sectiune puteti simula desfasurarea campionatelor");
											write (client, msgrasp, 100);
											strcpy(msgrasp,"Campionatele fac parte din urmatoarele sporturi:\n\n  -fotbal\n  -tenis\n  -ping-pong");
											write (client, msgrasp, 100);
											strcpy(msgrasp,"Introduceti optiunea dorita: ");
											write (client, msgrasp, 100);
											read (client, msg, 100);//citim de la client sportul ales 

											if(strncmp(msg,"fotbal",6)==0)
											{
												strcpy(msgrasp,"Campionate de fotbal disponibile:");
												write (client, msgrasp, 100);

												sqlite3_stmt *nume_fot;
												sqlite3_stmt *stare_fot;

												char l[700];
												char l1[700];
												sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_FOTBAL;", -1, &stare_fot, NULL);
												sqlite3_prepare(db, "SELECT NUME FROM TABELE_FOTBAL ;", -1, &nume_fot, NULL);
												while (sqlite3_step(nume_fot) == SQLITE_ROW && sqlite3_step(stare_fot) == SQLITE_ROW )
												{
													strcpy(l,(char*)sqlite3_column_text(nume_fot, 0));
													strcpy(msgrasp,l);
													write (client, msgrasp, 100);
													strcpy(l1,(char*)sqlite3_column_text(stare_fot, 0));
													strcpy(msgrasp,l1);
													write (client, msgrasp, 100);												
												}
												strcpy(msgrasp,"stop");
												write (client, msgrasp, 100);
												sqlite3_finalize(nume_fot);
												sqlite3_finalize(stare_fot);
											}
											//am afisat campionatele
											strcpy(msgrasp,"Introduceti optiunea dorita: ");
											write (client, msgrasp, 100);
											read (client, msg, 100);//citim de la client campionatul ales ales 
											msg[strlen(msg)-1]='\0';
											char nume_campionat1[100];
											strcpy(nume_campionat1,msg);
											char starea[256];
											//schimbam starea campionatului 
											
											sprintf(starea,"update TABELE_FOTBAL set STARE_CAMPIONAT='TERMINAT' where NUME like '%s';",nume_campionat1);
											rc = sqlite3_exec(db, starea, -1, 0, NULL);
											sqlite3_stmt *echipa1;
											sqlite3_stmt *echipa2;
											sqlite3_stmt *echipa3;
											char echi1[200];
											char echi2[200];
											char echi3[200];
											sprintf(echi1,"SELECT NUME FROM %s LIMIT 1 ;",nume_campionat1);
											sprintf(echi2,"SELECT NUME FROM %s LIMIT 1 OFFSET 1;",nume_campionat1);
											sprintf(echi3,"SELECT NUME FROM %s LIMIT 1 OFFSET 2;",nume_campionat1);
											sqlite3_prepare(db, echi1, -1, &echipa1, NULL);
											sqlite3_prepare(db, echi2, -1, &echipa2, NULL);
											sqlite3_prepare(db, echi3, -1, &echipa3, NULL);
											if(sqlite3_step(echipa1) == SQLITE_ROW && sqlite3_step(echipa2) == SQLITE_ROW && sqlite3_step(echipa3) == SQLITE_ROW)
											{
												strcpy(echi1,(char*)sqlite3_column_text(echipa1, 0));
												strcpy(echi2,(char*)sqlite3_column_text(echipa2, 0));
												strcpy(echi3,(char*)sqlite3_column_text(echipa3, 0));
												int scor1=rand()%7;
												int scor2=rand()%7;
												
												char sco1[700];
												char sco2[700];
												char sco3[700];
												//primu meci
												

												if(scor1==scor2)
												{
													sprintf(sco1,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi1);
													sprintf(sco2,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi2);
													
													rc = sqlite3_exec(db, sco1, callback, 0, &zErrMsg);
													rc = sqlite3_exec(db, sco2, callback, 0, &zErrMsg);
													
			
												}
												else
													if(scor1>scor2)
													{
														sprintf(sco1,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi1);
														rc = sqlite3_exec(db, sco1, callback, 0, &zErrMsg);
													}
													else
													{
														sprintf(sco2,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi2);
														rc = sqlite3_exec(db, sco2, callback, 0, &zErrMsg);	
													}
												strcpy(msgrasp,"\nSimularea primului meci...\n");
												write (client, msgrasp, 100);
												strcpy(msgrasp,"Meci incheiat! Scor:\n\n");
												write (client, msgrasp, 100);
												sprintf(msgrasp,"    %s  %d - %d  %s\n",echi1,scor1,scor2,echi2);
												write (client, msgrasp, 100);
												scor1=rand()%7;
												scor2=rand()%7;
												//al doilea meci


												if(scor1==scor2)
												{
													sprintf(sco1,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi1);
													sprintf(sco3,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi3);
													
													rc = sqlite3_exec(db, sco1, callback, 0, &zErrMsg);
													rc = sqlite3_exec(db, sco3, callback, 0, &zErrMsg);
			
												}
												else
													if(scor1>scor2)
													{
														sprintf(sco1,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi1);
														rc = sqlite3_exec(db, sco1, callback, 0, &zErrMsg);
													}
													else
													{
														sprintf(sco3,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi3);
														rc = sqlite3_exec(db, sco3, callback, 0, &zErrMsg);	
													}	
												strcpy(msgrasp,"\nSimularea celui de al doilea meci...\n");
												write (client, msgrasp, 100);
												strcpy(msgrasp,"Meci incheiat! Scor:\n\n");
												write (client, msgrasp, 100);
												sprintf(msgrasp,"    %s  %d - %d  %s\n",echi1,scor1,scor2,echi3);
												write (client, msgrasp, 100);
												scor1=rand()%7;
												scor2=rand()%7;
												//al treilea meci



												
												if(scor1==scor2)
												{
													sprintf(sco2,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi2);
													sprintf(sco3,"update %s set PUNCTE=PUNCTE+1 where NUME like '%s';",nume_campionat1,echi3);
													
													rc = sqlite3_exec(db, sco2, callback, 0, &zErrMsg);
													rc = sqlite3_exec(db, sco3, callback, 0, &zErrMsg);
			
												}
												else
													if(scor1>scor2)
													{
														sprintf(sco2,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi2);
														rc = sqlite3_exec(db, sco2, callback, 0, &zErrMsg);
													}
													else
													{
														sprintf(sco3,"update %s set PUNCTE=PUNCTE+3 where NUME like '%s';",nume_campionat1,echi3);
														rc = sqlite3_exec(db, sco3, callback, 0, &zErrMsg);	
													}	
												strcpy(msgrasp,"\nSimularea celui de al treilea meci...\n");
												write (client, msgrasp, 100);
												strcpy(msgrasp,"Meci incheiat! Scor:\n\n");
												write (client, msgrasp, 100);	
												sprintf(msgrasp,"    %s  %d - %d  %s\n",echi2,scor1,scor2,echi3);
												write (client, msgrasp, 100);

												//afisam castigatoarea
												char win[700];
												sqlite3_stmt *castigatoare;
												

												sprintf(sco2,"select NUME from %s order by  PUNCTE desc limit 1;",nume_campionat1);
												sqlite3_prepare(db,sco2, -1, &castigatoare, NULL);
												if(sqlite3_step(castigatoare)==SQLITE_ROW)
												{
													strcpy(win,(char*)sqlite3_column_text(castigatoare, 0));
													strcpy(msgrasp,"Castigatoarea este...  ");
													write (client, msgrasp, 100);
													strcpy(msgrasp,win);
													write(client,msgrasp,100);
													
												}
												sprintf(sco1,"update %s set STARE_JUCATOR='CASTIGATOARE' where PUNCTE=(select MAX(PUNCTE) from %s);",nume_campionat1,nume_campionat1);
												sprintf(sco2,"update %s set STARE_JUCATOR='PIERZATOARE' where STARE_JUCATOR='IN JOC';",nume_campionat1);
													
												rc = sqlite3_exec(db, sco1, callback, 0, &zErrMsg);
												rc = sqlite3_exec(db, sco2, callback, 0, &zErrMsg);

											}
											
											
											sqlite3_finalize(echipa1);
											sqlite3_finalize(echipa2);
											sqlite3_finalize(echipa3);
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
							strcpy(msgrasp,"Username sau parola gresita. Inapoi la sectiunea de logare");
							write (client, msgrasp, 100);
						}
					}			
					else 
						if(strncmp(msg,"n",1)==0)/*logare ca utilizator*/
						{
							strcpy(msgrasp,"Conectare ca utilizator...\n\n");
							write (client, msgrasp, 100);	

							strcpy(msgrasp,"Aveti cont de utilizator? [y/n] ");
							write (client, msgrasp, 100);
							read (client, msg, 100);//citim raspuns de la client 
							if(strncmp(msg,"y",1)==0)//are cont
							{
								strcpy(msgrasp,"Username utilizator: ");
								write (client, msgrasp, 100);
								read (client, msg, 100);//citim username
								//verificam username in baza de date					
								msg[strlen(msg)-1]='\0';
								sqlite3_stmt *res3;
								char sql3[1000];
								sprintf(sql3,"select * from UTILIZATORI where USERNAME like '%s'",msg);
								rc = sqlite3_prepare_v2(db, sql3, -1, &res3, NULL);
								int step3=sqlite3_step(res3);							
								if(step3 != SQLITE_DONE)
								{
									user_cu_parola++;
								}
								sqlite3_finalize(res3);
								strcpy(msgrasp,"Parola utilizator: ");
								write (client, msgrasp, 100);
								read (client, msg, 100);//citim parola
								//verificam parola
								msg[strlen(msg)-1]='\0';				
								sqlite3_stmt *res4;						
								sprintf(sql3,"select * from UTILIZATORI where PAROLA like '%s'",msg);
								rc = sqlite3_prepare_v2(db, sql3, -1, &res4, NULL);
								int step4=sqlite3_step(res4);
								if(step4 != SQLITE_DONE)
								{
									user_cu_parola++;													
								}		
								 sqlite3_finalize(res4);
								if(user_cu_parola==2)
								{
									strcpy(msgrasp,"Conectat ca utilizator");
									write (client, msgrasp, 100);//scriem conectat

									int optiuni_util=1;			
									while(optiuni_util==1)
									{
										strcpy(msgrasp,"\nOPTIUNI UTILIZATOR:");
										write (client, msgrasp, 100);
										strcpy(msgrasp,"  -vizualizare campionate\n  -inscriere\n  -inchidere conexiune\n\n");
										write (client, msgrasp, 100);
										strcpy(msgrasp,"Introduceti optiunea dorita: ");
										write (client, msgrasp, 100);
										read (client, msg, 100);//citim optiunea

										if(strncmp(msg,"vizualizare campionate",22)==0)
										{											
											strcpy(msgrasp,"In aceasta sectiune puteti urmari situatia ultimelor campionate");
											write (client, msgrasp, 100);
											strcpy(msgrasp,"Campionatele fac parte din urmatoarele sporturi:\n\n  -fotbal\n  -tenis\n  -ping-pong");
											write (client, msgrasp, 100);
											strcpy(msgrasp,"Introduceti optiunea dorita: ");
											write (client, msgrasp, 100);
											read (client, msg, 100);//citim sportul ales
											if(strncmp(msg,"tenis",5)==0)
											{
												strcpy(msgrasp,"Campionate de tenis disponibile:");
												write (client, msgrasp, 100);

												sqlite3_stmt *nume_tabele;
												sqlite3_stmt *stare_campionat;
												sqlite3_stmt *numarul;

												char b[700];
												char b1[700];
												char b2[700];
												sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_TENIS ;", -1, &stare_campionat, NULL);
												sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_TENIS ;", -1, &numarul, NULL);
												sqlite3_prepare(db, "SELECT NUME FROM TABELE_TENIS ;", -1, &nume_tabele, NULL);
												while (sqlite3_step(nume_tabele) == SQLITE_ROW && sqlite3_step(stare_campionat) == SQLITE_ROW && sqlite3_step(numarul) == SQLITE_ROW)
												{
													strcpy(b,(char*)sqlite3_column_text(nume_tabele, 0));
													strcpy(msgrasp,b);
													write (client, msgrasp, 100);
													strcpy(b1,(char*)sqlite3_column_text(stare_campionat, 0));
													strcpy(msgrasp,b1);
													write (client, msgrasp, 100);
													strcpy(b2,(char*)sqlite3_column_text(numarul, 0));
													strcpy(msgrasp,b2);
													write (client, msgrasp, 100);
													//afisam jucatorii

													sqlite3_stmt *Nume;
													sqlite3_stmt *stare_jucator;
													char test1[1000],test2[1000],test3[1000],test4[1000];
													sprintf(test1,"select NUME from %s;",b);
													sprintf(test2,"select STARE_JUCATOR from %s;",b);
													sqlite3_prepare(db, test1, -1, &Nume, NULL);
													sqlite3_prepare(db, test2, -1, &stare_jucator, NULL);
													while (sqlite3_step(Nume) == SQLITE_ROW && sqlite3_step(stare_jucator) == SQLITE_ROW)
													{
														strcpy(test3,(char*)sqlite3_column_text(Nume, 0));
														strcpy(msgrasp,test3);
														write (client, msgrasp, 100);
														strcpy(test4,(char*)sqlite3_column_text(stare_jucator, 0));
														strcpy(msgrasp,test4);
														write (client, msgrasp, 100);
													}
													sqlite3_finalize(Nume);
													sqlite3_finalize(stare_jucator);
													strcpy(msgrasp,"stop");
													write (client, msgrasp, 100);
													
												}
												strcpy(msgrasp,"stop");
												write (client, msgrasp, 100);
												sqlite3_finalize(nume_tabele);
												sqlite3_finalize(stare_campionat);
												sqlite3_finalize(numarul);
											}
											else
												if(strncmp(msg,"fotbal",6)==0)
												{
													strcpy(msgrasp,"Campionate de fotbal disponibile:");
													write (client, msgrasp, 100);

													sqlite3_stmt *nume_fot;
													sqlite3_stmt *stare_fot;

													char p[700];
													char p1[700];
													sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_FOTBAL;", -1, &stare_fot, NULL);
													sqlite3_prepare(db, "SELECT NUME FROM TABELE_FOTBAL ;", -1, &nume_fot, NULL);
													while (sqlite3_step(nume_fot) == SQLITE_ROW && sqlite3_step(stare_fot) == SQLITE_ROW )
													{
														strcpy(p,(char*)sqlite3_column_text(nume_fot, 0));
														strcpy(msgrasp,p);
														write (client, msgrasp, 100);
														strcpy(p1,(char*)sqlite3_column_text(stare_fot, 0));
														strcpy(msgrasp,p1);
														write (client, msgrasp, 100);
													
														//afisam echipele

														sqlite3_stmt *Nume3_fot;
														sqlite3_stmt *stare_echipa_fot;
														sqlite3_stmt *puncte_fot;

														char test1[1000],test2[1000],test3[1000],test4[1000],test5[1000],test6[1000];
														sprintf(test1,"select NUME from %s;",p);
														sprintf(test2,"select STARE_JUCATOR from %s;",p);
														sprintf(test3,"select PUNCTE from %s;",p);
														sqlite3_prepare(db, test1, -1, &Nume3_fot, NULL);
														sqlite3_prepare(db, test2, -1, &stare_echipa_fot, NULL);
														sqlite3_prepare(db, test3, -1, &puncte_fot, NULL);
														
														while (sqlite3_step(Nume3_fot) == SQLITE_ROW && sqlite3_step(stare_echipa_fot) == SQLITE_ROW && sqlite3_step(puncte_fot) == SQLITE_ROW)
														{
															
															strcpy(test4,(char*)sqlite3_column_text(Nume3_fot, 0));
															strcpy(msgrasp,test4);
															write (client, msgrasp, 100);
															strcpy(test5,(char*)sqlite3_column_text(stare_echipa_fot, 0));
															strcpy(msgrasp,test5);
															write (client, msgrasp, 100);
															strcpy(test6,(char*)sqlite3_column_blob(puncte_fot, 0));						
															strcpy(msgrasp,test6);
															write (client, msgrasp, 100);
															
														}
														sqlite3_finalize(Nume3_fot);
														sqlite3_finalize(stare_echipa_fot);
														sqlite3_finalize(puncte_fot);
														strcpy(msgrasp,"stop");
														write (client, msgrasp, 100);
														
													}
													strcpy(msgrasp,"stop");
													write (client, msgrasp, 100);
													sqlite3_finalize(nume_fot);
													sqlite3_finalize(stare_fot);

												}
												else
													if(strncmp(msg,"ping-pong",9)==0)
													{
														strcpy(msgrasp,"Campionate de ping-pong disponibile:");
														write (client, msgrasp, 100);

														sqlite3_stmt *nume_tabele;
														sqlite3_stmt *stare_campionat;
														sqlite3_stmt *numarul;

														char u22[700];
														char u122[700];
														char u222[700];
														sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_PING ;", -1, &stare_campionat, NULL);
														sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_PING ;", -1, &numarul, NULL);
														sqlite3_prepare(db, "SELECT NUME FROM TABELE_PING ;", -1, &nume_tabele, NULL);
														while (sqlite3_step(nume_tabele) == SQLITE_ROW && sqlite3_step(stare_campionat) == SQLITE_ROW && sqlite3_step(numarul) == SQLITE_ROW)
														{
															strcpy(u22,(char*)sqlite3_column_text(nume_tabele, 0));
															strcpy(msgrasp,u22);
															write (client, msgrasp, 100);
															strcpy(u122,(char*)sqlite3_column_text(stare_campionat, 0));
															strcpy(msgrasp,u122);
															write (client, msgrasp, 100);
															strcpy(u222,(char*)sqlite3_column_text(numarul, 0));
															strcpy(msgrasp,u222);
															write (client, msgrasp, 100);
															//afisam jucatorii
															sqlite3_stmt *Nume;
															sqlite3_stmt *stare_jucator;
															char test1[1000],test2[1000],test3[1000],test4[1000];
															sprintf(test1,"select NUME from %s;",u22);
															sprintf(test2,"select STARE_JUCATOR from %s;",u22);
															sqlite3_prepare(db, test1, -1, &Nume, NULL);
															sqlite3_prepare(db, test2, -1, &stare_jucator, NULL);
															while (sqlite3_step(Nume) == SQLITE_ROW && sqlite3_step(stare_jucator) == SQLITE_ROW)
															{
																strcpy(test3,(char*)sqlite3_column_text(Nume, 0));
																strcpy(msgrasp,test3);
																write (client, msgrasp, 100);
																strcpy(test4,(char*)sqlite3_column_text(stare_jucator, 0));
																strcpy(msgrasp,test4);
																write (client, msgrasp, 100);
															}
															sqlite3_finalize(Nume);
															sqlite3_finalize(stare_jucator);
															strcpy(msgrasp,"stop");
															write (client, msgrasp, 100);
															
														}
														strcpy(msgrasp,"stop");
														write (client, msgrasp, 100);
														sqlite3_finalize(nume_tabele);
														sqlite3_finalize(stare_campionat);
														sqlite3_finalize(numarul);
													}

										}									
											else
												if(strncmp(msg,"inchidere conexiune",19)==0)
												{
													printf("ok3");
													optiuni_util=0;
												}
												else
													if(strncmp(msg,"inscriere",9)==0)
													{
														strcpy(msgrasp,"Campionatele fac parte din urmatoarele sporturi:\n\n  -fotbal\n  -tenis\n  -ping-pong\n");
														write (client, msgrasp, 100);
														strcpy(msgrasp,"Introduceti optiunea dorita: ");
														write (client, msgrasp, 100);
														read (client, msg, 100);//citim sportul ales
														if(strncmp(msg,"tenis",5)==0)//optiuni inscriere la tenis
														{
															strcpy(msgrasp,"\n---Informatii---\n\n");
															write (client, msgrasp, 100);
															strcpy(msgrasp,"[campionatele de tenis sunt formate din 4 sau 8 jucatori]\n");
															write (client, msgrasp, 100);
															strcpy(msgrasp,"[aceste turnee sunt bazate pe structura single elimination]\n");
															write (client, msgrasp, 100);
															strcpy(msgrasp,"[campionatul va incepe doar cand se atinge numarul maxim de jucatori inscrisi(4 sau8)]\n");
															write (client, msgrasp, 100);
															strcpy(msgrasp,"[modul de extragere al partidelor este aleatoriu]\n\n\n");
															write (client, msgrasp, 100);
															strcpy(msgrasp,"Campionate disponibile:");
															write (client, msgrasp, 100);

															sqlite3_stmt *nume_tabele;
															sqlite3_stmt *stare_campionat;
															sqlite3_stmt *numarul;

															char t[1000];
															char t1[1000];
															char t2[1000];
															sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_TENIS ;", -1, &stare_campionat, NULL);
															sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_TENIS ;", -1, &numarul, NULL);
															sqlite3_prepare(db, "SELECT NUME FROM TABELE_TENIS ;", -1, &nume_tabele, NULL);
															while (sqlite3_step(nume_tabele) == SQLITE_ROW && sqlite3_step(stare_campionat) == SQLITE_ROW && sqlite3_step(numarul) == SQLITE_ROW)
															{
																strcpy(t,(char*)sqlite3_column_text(nume_tabele, 0));
																strcpy(msgrasp,t);
																write (client, msgrasp, 100);
																strcpy(t1,(char*)sqlite3_column_text(stare_campionat, 0));
																strcpy(msgrasp,t1);
																write (client, msgrasp, 100);
																strcpy(t2,(char*)sqlite3_column_text(numarul, 0));
																strcpy(msgrasp,t2);
																write (client, msgrasp, 100);
																printf("%s  %s  %s\n",t,t1,t2);
															}
															strcpy(msgrasp,"stop");
															write (client, msgrasp, 100);
															sqlite3_finalize(nume_tabele);
															sqlite3_finalize(stare_campionat);
															sqlite3_finalize(numarul);
															
															strcpy(msgrasp,"Introduceti numele campionatului la care vreti sa participati: ");
															write (client, msgrasp, 100);
															read (client, msg, 100);//citim numele campionatului
															msg[strlen(msg)-1]='\0';
															char campi[100];
															strcpy(campi,msg);
															strcpy(msgrasp,"Introduceti numele participantului: ");
															write (client, msgrasp, 100);
															read (client, msg, 100);//citim numele participantului
															msg[strlen(msg)-1]='\0';
															//inscriem participantul in campionat
															char sq4[1000];		
															sprintf (sq4,"INSERT INTO %s (NUME,STARE_JUCATOR) VALUES ('%s','IN JOC');",campi, msg);
															rc = sqlite3_exec(db, sq4, callback, 0, &zErrMsg);
															strcpy(msgrasp,"\nJucator inscris cu succes!\n\n");
															write (client, msgrasp, 100);
														}
														else
															if(strncmp(msg,"fotbal",6)==0)
															{
																strcpy(msgrasp,"\n---Informatii---\n\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"[campionatele de fotbal sunt formate din 3 echipe]\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"[aceste turnee sunt bazate pe structura Round-robin]\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"[campionatul va incepe doar cand se atinge numarul de 3 echipe inscrise]\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"[fiecare echipa va juca 2 meciuri-cate un meci cu fiecare adversar din grupa]\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"[modul de acordare al punctelor: victorie-3p ; egal-2p; infrangere-0p;]\n\n\n");
																write (client, msgrasp, 100);
																strcpy(msgrasp,"Campionate disponibile:\n");
																write (client, msgrasp, 100);
																//afisam campionatele
																sqlite3_stmt *nume_fot;
																sqlite3_stmt *stare_fot;
																char i[1000];
																char i1[1000];
																sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_FOTBAL;", -1, &stare_fot, NULL);
																sqlite3_prepare(db, "SELECT NUME FROM TABELE_FOTBAL;", -1, &nume_fot, NULL);
																while (sqlite3_step(nume_fot) == SQLITE_ROW && sqlite3_step(stare_fot) == SQLITE_ROW )
																{
																	strcpy(i,(char*)sqlite3_column_text(nume_fot, 0));
																	strcpy(msgrasp,i);
																	write (client, msgrasp, 100);
																	strcpy(i1,(char*)sqlite3_column_text(stare_fot, 0));
																	strcpy(msgrasp,i1);
																	write (client, msgrasp, 100);																	
																}
																strcpy(msgrasp,"stop");
																write (client, msgrasp, 100);
																sqlite3_finalize(nume_fot);
																sqlite3_finalize(stare_fot);

																strcpy(msgrasp,"Introduceti numele campionatului la care vreti sa participati: ");
																write (client, msgrasp, 100);
																read (client, msg, 100);//citim numele campionatului
																msg[strlen(msg)-1]='\0';
																char campi12[100];
																strcpy(campi12,msg);
																strcpy(msgrasp,"Introduceti numele participantului: ");
																write (client, msgrasp, 100);
																read (client, msg, 100);//citim numele echipei
																msg[strlen(msg)-1]='\0';
																//inscriem echipa in campionat
																char st[1000];		
																sprintf (st,"INSERT INTO %s (NUME,PUNCTE,STARE_JUCATOR) VALUES ('%s',0,'IN JOC');",campi12, msg);
																rc = sqlite3_exec(db, st, callback, 0, &zErrMsg);
																strcpy(msgrasp,"\nEchipa inscrisa cu succes!\n\n");
																write (client, msgrasp, 100);
															}
															else
																if(strncmp(msg,"ping-pong",9)==0)//optiuni inscriere la ping-pong
																{
																	strcpy(msgrasp,"\n---Informatii---\n\n");
																	write (client, msgrasp, 100);
																	strcpy(msgrasp,"[campionatele de ping-pong sunt formate din 4 sau 8 jucatori]\n");
																	write (client, msgrasp, 100);
																	strcpy(msgrasp,"[aceste turnee sunt bazate pe structura single elimination]\n");
																	write (client, msgrasp, 100);
																	strcpy(msgrasp,"[campionatul va incepe doar cand se atinge numarul maxim de jucatori inscrisi(4 sau8)]\n");
																	write (client, msgrasp, 100);
																	strcpy(msgrasp,"[modul de extragere al partidelor este aleatoriu]\n\n\n");
																	write (client, msgrasp, 100);
																	strcpy(msgrasp,"Campionate disponibile:");
																	write (client, msgrasp, 100);

																	sqlite3_stmt *nume_tabele1;
																	sqlite3_stmt *stare_campionat1;
																	sqlite3_stmt *numarul1;

																	char t11[1000];
																	char t111[1000];
																	char t211[1000];
																	sqlite3_prepare(db, "SELECT STARE_CAMPIONAT FROM TABELE_PING;", -1, &stare_campionat1, NULL);
																	sqlite3_prepare(db, "SELECT NR_JUCATORI FROM TABELE_PING ;", -1, &numarul1, NULL);
																	sqlite3_prepare(db, "SELECT NUME FROM TABELE_PING ;", -1, &nume_tabele1, NULL);
																	while (sqlite3_step(nume_tabele1) == SQLITE_ROW && sqlite3_step(stare_campionat1) == SQLITE_ROW && sqlite3_step(numarul1) == SQLITE_ROW)
																	{
																		strcpy(t11,(char*)sqlite3_column_text(nume_tabele1, 0));
																		strcpy(msgrasp,t11);
																		write (client, msgrasp, 100);
																		strcpy(t111,(char*)sqlite3_column_text(stare_campionat1, 0));
																		strcpy(msgrasp,t111);
																		write (client, msgrasp, 100);
																		strcpy(t211,(char*)sqlite3_column_text(numarul1, 0));
																		strcpy(msgrasp,t211);
																		write (client, msgrasp, 100);
																		printf("%s  %s  %s\n",t11,t111,t211);
																	}
																	strcpy(msgrasp,"stop");
																	write (client, msgrasp, 100);
																	sqlite3_finalize(nume_tabele1);
																	sqlite3_finalize(stare_campionat1);
																	sqlite3_finalize(numarul1);
																	strcpy(msgrasp,"Introduceti numele campionatului la care vreti sa participati: ");
																	write (client, msgrasp, 100);
																	read (client, msg, 100);//citim numele campionatului
																	msg[strlen(msg)-1]='\0';
																	char campi1[100];
																	strcpy(campi1,msg);
																	strcpy(msgrasp,"Introduceti numele participantului: ");
																	write (client, msgrasp, 100);
																	read (client, msg, 100);//citim numele participantului
																	msg[strlen(msg)-1]='\0';
																	//inscriem participantul in campionat
																	char sq41[1000];		
																	sprintf (sq41,"INSERT INTO %s (NUME,STARE_JUCATOR) VALUES ('%s','IN JOC');",campi1, msg);
																	rc = sqlite3_exec(db, sq41, callback, 0, &zErrMsg);
																	strcpy(msgrasp,"\nJucator inscris cu succes!\n\n");
																	write (client, msgrasp, 100);
																}
													}
									}								
								}
								else
								{
									strcpy(msgrasp,"username sau parola gresita. incercati din nou \n");
									write (client, msgrasp, 100);//scriem "username sau parola gresita. incercati din nou 
								}
							}
							else //utilizatorul nu are cont=>inregistrare
							{
								strcpy(msgrasp,"Inregistrare utilizator nou.... \n");
								write (client, msgrasp, 100);
								strcpy(msgrasp,"Username: ");
								write (client, msgrasp, 100);

								read (client, msg, 100);//citim username util nou								

								char copie_user[200];
								strcpy(copie_user,msg);
								copie_user[strlen(copie_user)-1]='\0';
							
								strcpy(msgrasp,"Parola: ");
								write (client, msgrasp, 100);								
								read(client, msg, 100);//citim parola util nou
								char copie_parola[200];
								strcpy(copie_parola,msg);
								copie_parola[strlen(copie_parola)-1]='\0';
								//introducem util nou cu parola in baza de date
								
								char sql4[1000];
														
								sprintf (sql4,"INSERT INTO UTILIZATORI (USERNAME,PAROLA) VALUES ('%s','%s');",copie_user, copie_parola);
   								rc = sqlite3_exec(db, sql4, callback, 0, &zErrMsg);
								strcpy(msgrasp,"Utilizator inregistrat cu succes! \n");
								write (client, msgrasp, 100);
								strcpy(msgrasp,"Inapoi la sectiunea de logare... \n");
								write (client, msgrasp, 100);
							}

						}
				}while( user_cu_parola <2 );
			sqlite3_close(db);
			close (client);
			exit(0);
			
    		}

    }			
}				