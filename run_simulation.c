#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
*************************************************************************************READ ME*****************************************************************************************
						1.)first run the c code "run_simulation_EP19BTECH11004.c"  it will simulate the sir 
						epidemic and it will print out the number of succeptable , infected and 
						recovered individuals at each increment of time it will also write this 
						data to "output.txt" 
						2.)then run the python code "plot_graph.py" it will read the "output.txt" and 
						plot graph 


						you can adjust the maximum vertices and maxmium edges per vertex by changing
 						the "MAX_VERTICES", "MAX_EDGES", maximum_time(just below this comment ),i have 
 						set maximum vertex to 5000 and maximum edges to 100 for faster calculation 

						important if you are changing the maximum_time of simulation you
						 should make necessary changes in the for loop of python script
						(if time =300 for loop should be" for i in range (0 ,301) " )
****************************************************************************************************************************************************************************************
*/


//hyperparameters
int initial_number_of_infected; 
#define MAX_VERTICES 5000
#define MAX_EDGES 50
#define maximum_time 300







int numberofvertices;
int maxnumberofedges;



//global variables for keeping track of the number of
//suceeptable ,infected and recoverd
int number_of_suceecptable=0;
int number_of_infected=0;
int number_of_recoverd=0;





																//dtata type for storing the details
																//of vertex in a graph 
																struct Graph_vertex
																{
																char status;
																struct Graph_vertex * next;
																struct Edge * linked_list_of_pointers_of_neighbour;
																int number_of_neigbours;
																};
																//data type for storing the edges
																//edges=linking between vertex

															/*
															the pointers to neigbours are stored in a linked
															list with head pointer  "linked_list_of_pointers_of_neighbour"
															of each struct Graph_vertex
															*/




																struct Edge
																{
																struct Graph_vertex * pointer_to_neigbour;
																struct Edge* next;
																};

 

																struct Heap_node
																{
																int time;
																
																struct Graph_vertex * vertex;
																char event_to_process;
																struct Heap_node * next;
																};
																/*
																first element (element coreesponding to index 0
																) in the linked list for impleneting heap will
																be like a dummy element i wont use that to store
																the event i will use elements from index 1 onwards
																*/


													//functions for maintaining heap


													struct Heap_node* heap_head=NULL;
													int number_of_nodes_in_heap=0;


													int heap_add(int time,char event_to_process,struct Graph_vertex * vertex);
													struct Heap_node * getparent( struct Heap_node * child);
													struct Heap_node * getparent( struct Heap_node * child);
													struct Heap_node * nav_h(int index);
													struct Heap_node * getleftchild( struct Heap_node * parent);
													struct Heap_node * getrightchild( struct Heap_node * parent);
													int heapifydown();
													int heapifyup();
													int print_heap();
													int getindex(struct Heap_node * heap_node);
													int swap(struct Heap_node *e1,struct Heap_node *e2);




													struct Heap_node * getminnode();





													//functions for maintaining graph
													struct Edge * last_ele_linked_list_neigbours(struct Graph_vertex* vertx);
													struct Graph_vertex * nav(int index);
													int connect(struct Graph_vertex* e1,struct Graph_vertex* e2);
													struct Edge * last_ele_linked_list_neigbours(struct Graph_vertex* vertx);




													struct Graph_vertex* head_vertex=NULL;





													int print_graph();
													int connect_vertex_graph();
													int initilize_graph();



















int initilize_sir_simulation();
int process_queue();
int infect(struct Graph_vertex* vertex_to_infect,int time_of_infection);
int transmit_to_neighbour(struct Graph_vertex* vertex_to_infect,int time);
int print_sir_list(int time);







int index_printer(struct Graph_vertex* vertex);



FILE *file_pointer;

//#################################################################  MAIN   ######################################################################################################

int main(void)
{
srand ( time(NULL) );


file_pointer=fopen("output.txt","w");



initial_number_of_infected=rand()%300;



initilize_graph();
connect_vertex_graph();
//print_graph();


printf("\n completed graph initilizing graph\n");
initilize_sir_simulation();
printf("\n processing q");
process_queue();
printf("\n completed \n printing heap\n");
print_heap();
//print_graph();


fclose(file_pointer);

return 0;
}

//#############################################################################3  index of vertex finder ###############################################################################
int index_printer(struct Graph_vertex* vertex)
{
struct Graph_vertex* tmp=NULL;
tmp=head_vertex;


							for(int h=0;h<numberofvertices;h++)
							{
										if(tmp==vertex)
										{printf(" index (%d )",h);}
							tmp=tmp->next;
							}

return 0;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  sir handling function $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//##################################################################   simulation inittilizing function   ########################################################################

int initilize_sir_simulation()
{
heap_head=(struct Heap_node*)malloc( sizeof(struct Heap_node)) ;
//allocating memory for heap head

			for(int i=0;i<initial_number_of_infected;i++)
			{
			nav(i)->status='I';
			//PUT IN QUEUE infect function will put both recovery event and transmission event in queue
			infect(nav(i),0);
			}

			number_of_infected=initial_number_of_infected;



					for(int i=initial_number_of_infected;i<numberofvertices;i++)
					{
					nav(i)->status='S';
					//making all other nodes sucecptable
					}
					number_of_suceecptable=numberofvertices-initial_number_of_infected;

					printf("initial status t=0: I=%d S=%d R=%d\n",number_of_infected,number_of_suceecptable,number_of_recoverd);





return 0;
}
//#######################################################################  infect _node ###############################################################################################

int infect(struct Graph_vertex* vertex_to_infect,int time_of_infection)
{

//for loop all neigbours 
//if sucepptable calculate time and put in p queue





//########TRANSMISSION
struct Edge * tmp=NULL;
tmp=vertex_to_infect->linked_list_of_pointers_of_neighbour;



int num_of_vertex_to_infect=vertex_to_infect->number_of_neigbours;

		for(int i=0;i<num_of_vertex_to_infect;i++)
		{
		transmit_to_neighbour(tmp->pointer_to_neigbour,time_of_infection);
		tmp=tmp->next;
		}


//transmit to neigbour function will calculate time for transmission and put it in queue
//running for loop for transmitting to all neigbours,calling transmit to neigbour function with  each neigbour as argument



//###############RECOVERY
//determing time for recovery and put in queue if time of recovery is less than or equal to maximum time

int time_req_for_recovery=0;
int x;


			while(1)
			{


			x=rand()%5;
			time_req_for_recovery++;


if(x==4){break;}
if(time_req_for_recovery>maximum_time)
{break;}

			}

		int total_time_r=time_req_for_recovery+time_of_infection;


				if(total_time_r<=maximum_time)
					{heap_add(total_time_r,'R',vertex_to_infect);}
return 0;
}

//################################################################  transmitt to neighbours ###########################################################################################
int transmit_to_neighbour(struct Graph_vertex* vertex_to_infect,int time)
{



int x;
int time_taken_to_infect=0;

		while(1)
		{
		int x=rand()%2;
		time_taken_to_infect++;

		if(x==1){break;}
		}



			int total_time=time_taken_to_infect+time;


			if(total_time<=maximum_time)
			{

			heap_add(total_time,'T',vertex_to_infect);
			}



//transmission function calculte time for transmission and if that time is less than or equal to max time put that to queue


return 0;
}
//############################################################################### process queue ######################################################################################
int process_queue()
{

/*
while loop 
breaks if queu is empty 
or 
time is greater than maxtime
*/


	int current_time=0;

	while(1)
	{

	/*
	heap will only contain upto max time
	so heap is empty means events upto
	max time is done
	*/
	if(number_of_nodes_in_heap==0)
			{

			print_sir_list(current_time);

			break;}

	struct Heap_node * earliest_remaining_element=getminnode();
	struct Graph_vertex *coressponding_vertex=earliest_remaining_element->vertex;

	int earliest_remaining_element_time=earliest_remaining_element->time;


	if(current_time<earliest_remaining_element_time)
	{


			while(current_time<earliest_remaining_element_time)
			{
			print_sir_list(current_time);
			current_time++;
			}
	//current_time=earliest_remaining_element->time;
	}
	


				char status_of_earliest_remaining_element=earliest_remaining_element->event_to_process;



				if(status_of_earliest_remaining_element=='T')
				{
						char coressponding_vertex_status=coressponding_vertex->status;

						if(coressponding_vertex_status=='S')
						{
						coressponding_vertex->status='I';
						infect(coressponding_vertex,earliest_remaining_element->time);
						number_of_suceecptable--;
						number_of_infected++;

						}
				}
				else if(status_of_earliest_remaining_element=='R')
					{
					coressponding_vertex->status='R';
					number_of_infected--;
					number_of_recoverd++;

					}


//print_sir_list(current_time);


	}


	while(current_time<maximum_time)
	{
	current_time++;
	print_sir_list(current_time);
	}


		
return 0;
}
//############################################################################  print s i r list #######################################################################################
int print_sir_list(int time)
{
//go through graph 
//take the s element and print
//take the r element and print
//take the i elemnts and print

printf("\n\nstatus#### t=%d::: I=%d S=%d R=%d\n\n",time,number_of_infected,number_of_suceecptable,number_of_recoverd);


fprintf(file_pointer,"%d %d %d %d \n",time,number_of_infected,number_of_suceecptable,number_of_recoverd);


printf("\n   time::%d   \n",time);



return 0;
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  sir handling function END $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    functions helping graph function   %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%




//################################################################################### nav in the linked list of vetex################################################################

struct Graph_vertex * nav(int index)
{
		if(index>numberofvertices-1)//-1 beacuse index start counting from zero
		{
		return NULL;
		}

		struct Graph_vertex* tmp=NULL;
		tmp=head_vertex;
				for(int i=0;i<index;i++)
				{
				tmp=tmp->next;
				}

return tmp;


}

//###############################################################  print_graph #########################################################################################################

int print_graph()
{
	printf(" ");
	for(int i=0;i<numberofvertices;i++)
	{
		int x_y=nav(i)->number_of_neigbours;
		char s=nav(i)->status;
		printf("[%d-num og neig=%d  [%c]]::",i,x_y,s);


		int x=nav(i)->number_of_neigbours;
		struct Edge* tmp=NULL;
		tmp=nav(i)->linked_list_of_pointers_of_neighbour;

		for(int k=0;k<x;k++)
		{
			struct Graph_vertex* tmpv=NULL;
			tmpv=tmp->pointer_to_neigbour;

							for(int h=0;h<numberofvertices;h++)
							{
										if(tmpv==nav(h))
										{printf(" %d ",h);}			
							}
			tmp=tmp->next;
		}
printf("\n ");
	}
return 0;
}
//###############################################################  connect vertex of graph  #########################################################################################
int connect_vertex_graph()
{
//creating  edges
for(int i=0;i<numberofvertices;i++)
{
		for(int k=0;k<maxnumberofedges;k++)
		{
				if(rand()%2==1)
				{
				//nav vertices 
				//nav edges using while loop untill null pointer 
				//find a rand vertex and connect it to edge 
				int index_of_other_vertex;

				index_of_other_vertex=rand()%numberofvertices;
								
						if(index_of_other_vertex!=i)
						{connect(nav(i),nav(index_of_other_vertex));}				
				}
		}
}

return 0;}
//###################################################################  initilize graph   ############################################################################################
int initilize_graph()
{
/*intilizing the value of number 
of vertex and maximum allowed edges
 using random number generator*/


numberofvertices = rand() % MAX_VERTICES;




maxnumberofedges = rand() % MAX_EDGES;





if( numberofvertices == 0)
   {numberofvertices++;}


printf("Total Vertices = %d, Max # of Edges = %d\n",numberofvertices, maxnumberofedges);

//allocating memeory for head ,which is head of linked list 
//containing vertexes 
head_vertex=(struct Graph_vertex*)malloc(sizeof( struct Graph_vertex));



struct Graph_vertex* temp=NULL;
temp=head_vertex;


	//for initilizing all vertices
	for(int i=0;i<numberofvertices;i++)
	{
	struct Graph_vertex* tmp=NULL;
	tmp=(struct Graph_vertex*)malloc(sizeof( struct Graph_vertex));

	//give value to tmp
	tmp->next=NULL;
	tmp->number_of_neigbours=0;
	tmp->linked_list_of_pointers_of_neighbour=NULL;

	temp->next=tmp;
	temp=tmp;//preparing for next cycle
	}

return 0;}
//################################################################## connect #######################################################################################################
int connect(struct Graph_vertex* e1,struct Graph_vertex* e2)
{
	if(e1->number_of_neigbours==maxnumberofedges||e2->number_of_neigbours==maxnumberofedges)
	{return 1;}
//if vertex has number of neighbiours equal to maximum allowed function exits




	//adding to first elements list
	if(e1->number_of_neigbours==0)
	{

	struct Edge* tmp=NULL;
	tmp=(struct Edge*)malloc(sizeof( struct Edge));


	tmp->pointer_to_neigbour=e2;
	tmp->next=NULL;

	e1->linked_list_of_pointers_of_neighbour=tmp;

	}
		else
		{

		struct Edge* tmp=NULL;
		tmp=(struct Edge*)malloc(sizeof( struct Edge));


		tmp->pointer_to_neigbour=e2;
		tmp->next=NULL;

		last_ele_linked_list_neigbours(e1)->next=tmp;


		}


		//adding to second elements list
		if(e2->number_of_neigbours==0)

		{

		struct Edge* tmp2=NULL;
		tmp2=(struct Edge*)malloc(sizeof( struct Edge));


		tmp2->pointer_to_neigbour=e1;
		tmp2->next=NULL;

		e2->linked_list_of_pointers_of_neighbour=tmp2;

		}
					else
					{

					struct Edge* tmp2=NULL;
					tmp2=(struct Edge*)malloc(sizeof( struct Edge));


					tmp2->pointer_to_neigbour=e1;
					tmp2->next=NULL;

					last_ele_linked_list_neigbours(e2)->next=tmp2;
					}


e1->number_of_neigbours++;
e2->number_of_neigbours++;

return 0;
}

//################################################################  nav edges #####################################################################################################
struct Edge * last_ele_linked_list_neigbours(struct Graph_vertex* vertx)
{
		struct Edge* tmp=NULL;
		tmp=vertx->linked_list_of_pointers_of_neighbour;

		int index_of_last_node=vertx->number_of_neigbours-1;

				for(int i=0;i<index_of_last_node;i++)
				{
				tmp=tmp->next;
				}

		return tmp;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    functions helping graph   END %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
























//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& functions helping  heap maintanace &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&








//######################################################################## Add #############################################################################################
int heap_add(int time,char event_to_process,struct Graph_vertex * vertex)
{
//add to tail
//heapify up
struct Heap_node* tmp=NULL;
tmp=(struct Heap_node*)malloc( sizeof(struct Heap_node)) ;
struct Heap_node* ele_to_be_added=NULL;
 ele_to_be_added=(struct Heap_node*)malloc( sizeof(struct Heap_node)) ;

ele_to_be_added->next=NULL;
ele_to_be_added->time=time;
ele_to_be_added->event_to_process=event_to_process;
ele_to_be_added->vertex=vertex;

tmp=nav_h(number_of_nodes_in_heap);
tmp->next= ele_to_be_added;

number_of_nodes_in_heap++;

heapifyup();

  return 0;
}
//########################################################################## get parents ###################################################################################
struct Heap_node * getparent( struct Heap_node * child)
{
int child_index=getindex(child);

//index based
//call  nav functions
int parent_index=child_index/2;

if(parent_index==0)
{
return NULL;
}


return nav_h(parent_index);
}
//############################################################################ nav #############################################################################################
struct Heap_node * nav_h(int index)
{

//for loop retuens corresponding ele
struct Heap_node* tmp=NULL;
tmp=(struct Heap_node*)malloc( sizeof(struct Heap_node)) ;
tmp=heap_head;



    for(int i=0;i<index;i++)
    {
	tmp=tmp->next;
    }


  return tmp;
}




//################################################################### getleftchild ################################################################################################

struct Heap_node * getleftchild( struct Heap_node * parent)
{
//index calculation
  //call nav
int parent_index=getindex(parent)  ;
 int child_index=parent_index*2;

if(child_index>number_of_nodes_in_heap)
{return NULL;}


return nav_h(child_index)  ;
}
//################################################################### getright child #######################################################################################
struct Heap_node * getrightchild( struct Heap_node * parent)
{
//index call
//call nav
int parent_index=getindex(parent)  ;


 int child_index=parent_index*2+1;

if(child_index>number_of_nodes_in_heap)
{return NULL;}


return nav_h(child_index)  ;
}

//######################################################################  heapifydown ###############################################################################################

int heapifydown()
{
//take root compare go down while end of loop

struct Heap_node* tmp;
tmp=nav_h(1);

			while(1)
			{

			//break if end of array
			//break if root is the lowest 


					if(getleftchild(tmp)==NULL)
					{
					/*
					if no left child obiviously no rightchild
					therefore we can stop 
					*/



					break;

					}



					int parent_t=tmp->time;
					int child_l_t=getleftchild(tmp)->time;
					struct Heap_node* smallest_child;
					smallest_child=getleftchild(tmp);





					if(getrightchild(tmp)!=NULL)
					{
					//checking if right child exsisit or not 
						int child_r_t=getrightchild(tmp)->time;


						if(child_r_t<child_l_t)
						{//time of right child less than left then
						//smallest child is right child
						smallest_child=getrightchild(tmp);
						}
					}

					int s_t=smallest_child->time;

					//if smallest child has time less than
					//parent then swap else break
					if(s_t<parent_t)
					{swap(tmp,smallest_child);}
						else
						{break;}


tmp=smallest_child;
			
			}




  return 0;
}
//################################################################### heapify up ###############################################################################################
int heapifyup()
{
//take tail end go up untill end of array

struct Heap_node* tmp=NULL;
tmp=nav_h(number_of_nodes_in_heap);

while (1)
{

if(getparent(tmp)==NULL)
{break;}


int child_t=tmp->time;
int parent_t=getparent(tmp)->time;

if(child_t<parent_t)
{swap(tmp,getparent(tmp));}
else
{ break;  }

tmp=getparent(tmp);

}
  return 0;
}

//#################################################################### print heap #################################################################################################
int print_heap()
{
  struct Heap_node* tmp=NULL;
  tmp=(struct Heap_node*)malloc( sizeof(struct Heap_node)) ;
printf("\nheap:");
          for(int i=1;i<=number_of_nodes_in_heap;i++)
          {
          tmp=nav_h(i);
            printf(" {t:%d,s:%c",tmp->time,tmp->event_to_process);
	index_printer(tmp->vertex);
printf(" -- ");


          }
          printf("\n");
  return 0;
}
//################################################################### get index ##########################################################################################


int getindex(struct Heap_node * heap_node)
{
int index;
struct Heap_node * tmp=NULL;
tmp=heap_head;
    for(int i= 1;i<=number_of_nodes_in_heap;i++)
    {

    tmp=tmp->next;

                    if(tmp==heap_node)
                    {
                    index=i;
                      break;
                    }
    }
tmp=NULL;
  return index;
}


//################################################################################## swap 2 elements #####################################################################################

int swap(struct Heap_node *e1,struct Heap_node *e2)
{
int temp_time;
char temp_process;
struct Graph_vertex * temp_vertex;

temp_time=e1->time;
temp_process=e1->event_to_process;
temp_vertex=e1->vertex;

e1->time=e2->time;
e1->event_to_process=e2->event_to_process;
e1->vertex=e2->vertex;

e2->time=temp_time;
e2->event_to_process=temp_process;
e2->vertex=temp_vertex;
  return 0;
}
//#####################################################################  poll ###########################################################################################################
struct Heap_node * getminnode()
{

			if(number_of_nodes_in_heap<=0)
			{return NULL;}
					else if(number_of_nodes_in_heap==1)
					{
					struct Heap_node *tmp=NULL;
					tmp=nav_h(1);
					number_of_nodes_in_heap--;
					return tmp;
					}



							else
							{
							struct Heap_node *root=NULL;
							root=nav_h(1);

							struct Heap_node * last_node=NULL;
							last_node=nav_h(number_of_nodes_in_heap);

							struct Heap_node * second_last_node=NULL;
							second_last_node=nav_h(number_of_nodes_in_heap-1);

							swap(root,last_node);
							//breaking old bonds and formming new ones

							second_last_node->next=NULL;

							number_of_nodes_in_heap--;							
							heapifydown();

							return last_node;
							}
}

////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& functions helping  heap maintanace END &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&






