#include <stdio.h>

#include <vector>
//! 

typedef std::vector<int> VecInt;
typedef std::vector<VecInt> Matr;


struct bond_
{
    int id1;
    int id2;
    int kind;
    //! The constructor.
    bond_(int _id1, int _id2, int _kind): id1(_id1), id2(_id2),kind(_kind) {};
};

typedef std::vector<bond_> BondsData;

#if 0
typedef int abond[2];
typedef abond* TheBonds;
abond b1 = {1,2};
abond b2 = {2,3};
TheBonds bonds;
bonds = calloc (nbonds, 2*sizeof(int) );

int **bonds=NULL;	/* matrix nbonds x 2 */
bonds = (int **) calloc( n, sizeof(int *) );
if ( !bonds )  "Not enough memory for matrix"
for (i=0; i<nbonds; i++)
{
	bonds[i] = (int *) calloc( 2, sizeof(int) );
	if ( !bonds[i] ) "Not enough memory for matrix";
}
#endif



#define PM_BO_SINGLE 0
#define PM_BO_DOUBLE 2
#define PM_BO_TRIPLE 4 
#define PM_BO_QUARTRY 8
#define PM_BO_AROMATIC 16
#define PM_BO_ANY 64


#if 0
const A : matr = (( 0,1,0,1,0,0,0,1,0), 
(1,0,1,0,0,1,0,0,0), 
(0,1,0,1,1,0,1,0,0), 
(1,0,1,0,0,0,1,0,0), 
(0,0,1,0,0,0,0,1,1), 
(0,1,0,0,0,0,0,0,0), 
(0,0,1,1,0,0,0,0,0), 
(1,0,0,0,1,0,0,0,0), 
(0,0,0,0,1,0,0,0,0)); 
#endif


//! Just visit all the vertexes.
void zdfs( Matr& A, int X, VecInt& R);


//! Find all paths.
void zdfs_paths_matr( Matr& A, int X);
void zdfs_paths( BondsData& BD, int X);
void zdfs_paths_all( BondsData& bonds, int at0, int maxlen, int maxpaths);

int  czdfs_paths_all( int nbonds, BondsData& edges, int at0, int maxlen, int maxpaths);





typedef struct tagEdge
{
    int lt;
	int rt;
	int type;
} EDGE;

typedef struct tagDFS
{
	/* Number of nodes */
	int nn;					
	/* Number of edges */
	int ne;					
	EDGE *edges;
	int *discovered;	
	int	*parent;		
	int	*processed;		
	int completed;
	int passed;
	int end;
	/* Hook function */
	int		(*treat_node)(int);
	/* Hook function */
	int		(*treat_edge)(int,int);
} DFSEARCH;

DFSEARCH * dfs_new(int nn, int ne, EDGE *e );
void dfs_reset( DFSEARCH *dfs );
void dfs_free( DFSEARCH *dfs );
void dfs_run(DFSEARCH *dfs, int v, int* ids);



#if 0
typedef struct light_mg
{
	ORIG_ATOM_DATA *orig_at_data;
	int *at;	/* atom numbers; bonds come from orig_at_data */
	int *adj[MAXVAL];
	int nvisited;
	int *visited;
} light_mg;



/* adj is bonds as nbonds x MAXVAL matrix ( bond[0, 1, 2] are {i, j, kind} ) */
int  czdfs_paths_all( int nat, int nbonds, int **edges, int at0, int maxlen, int maxpaths)
{
int j, k, r, v;
int npaths=0, err;
int b, c;			/* boolean */
int *stack=NULL; 
int **a=NULL;		/* adjacency matrix nat x nat									*/
int **passed=NULL;	/* passed[i][j] = 1 means that the edge (i,j) has been visited.	*/


	err = 1;
	stack = (int *) calloc( nat, sizeof(int));			
	if ( !stack)
		goto exitf;
	if ( imat_new( nat, nat, &a ) )	
		goto exitf;
	if ( imat_new( nat, nat, &passed ) )	
		goto exitf;
	err = 0;

    for (r=0; r<nbonds; r++)
    {
		int at1 = edges[r][0];
		int at2 = edges[r][1];
        a[at2][at1] = a[at1][at2] = edges[r][2];
    }



void jdfs(
		  int *nvisited, int *visited, ) 
{
	int k;
	int atom;	/* 'atom's starts from 1, 'node's starts from 0 */







	//for (String node : nodes) {
	for (k=0; k<orig_at_data->at[a].valence; k++)
	{

        if ( orig_at_data->at[a].neighbor[k] != b )
            continue;


            if (visited.contains(node)) {
                continue;
            }
            if (node.equals(END)) {
                visited.add(node);
                printPath(visited);
                visited.removeLast();
                break;
            }
        }
        for (String node : nodes) {
            if (visited.contains(node) || node.equals(END)) {
                continue;
            }
            visited.addLast(node);
            jdfs(graph, visited);
            visited.removeLast();
        }

		return;
}

    private void printPath(LinkedList<String> visited) {
        for (String node : visited) {
            System.out.print(node);
            System.out.print(" ");
        }
        System.out.println();
    }

#endif



/*  Allocate memory for int a[m][n] matrix */
int imat_new( int m, int n, int ***a )
{
int i;
	*a = ( int **)	calloc( m, sizeof( int * ) );
	if (NULL==*a)	return 1;
	for (i=0;i<m;i++)
	{
		(*a)[i] =				(int *) calloc( n,sizeof( int ));
		if ( NULL==(*a)[i] )	return 1;
    }
	return 0;
}
/*  Free memory of a[m][n] matrix */
void imat_free( int m, int **a )
{
int i;
	if ( NULL!= a )
	{
		for ( i=0; i<m; i++ )	if ( NULL!=a[i] )	free(a[i]);
		free( a );
	}
	return;
}
/* */
DFSEARCH *dfs_new(int nn, int ne, EDGE *e )
{
	DFSEARCH *dfs = NULL; 

	dfs = (DFSEARCH *) calloc(1, sizeof(DFSEARCH));

	if ( !dfs )
		return NULL;
	
	dfs->nn = nn;
	dfs->ne = ne;
	dfs->edges = e;
	
	dfs->discovered = dfs->parent = dfs->processed = NULL;
	dfs->discovered = (int *) calloc( nn+1, sizeof(int) );
	if ( !dfs->discovered )
		return NULL;
	dfs->parent = (int *) calloc( nn+1, sizeof(int) );
	if ( !dfs->parent )
		return NULL;
	dfs->processed = (int *) calloc( nn+1, sizeof(int) );
	if ( !dfs->processed )
		return NULL;


	dfs_reset( dfs );
	
	return dfs;
}
void dfs_reset( DFSEARCH *dfs )
{
int i;
	for (i=0; i<dfs->nn+1; i++) 
	{
		dfs->processed[i] = dfs->discovered[i] = 0;
		dfs->parent[i] = -1;
	}
	dfs->completed = dfs->passed = 0;
	dfs->end = -1;
}
/* Destructor */
void dfs_free( DFSEARCH *dfs )
{
	if ( dfs )				
	{
		if ( dfs->edges )		free(dfs->edges);
		if ( dfs->discovered )	free( dfs->discovered );
		if ( dfs->parent )		free( dfs->parent );
		if ( dfs->processed )	free( dfs->processed );
	free( dfs );
	}
}
/* DFS search starting from node v and fill in ids; */
void dfs_run(DFSEARCH *dfs, int v, int* ids)
{
int i;
int y;

	if ( v < 1 )
		return;

	/*! Mark this node as visited */
	dfs->discovered[v] = 1;

	/*! For each connected vertex ( == for each edge from v)*/
	for (i=0; i<dfs->ne; i++)
	{
		/*! Select next edge to v*/

		/*! Is bond to current node v?*/
		if ( (dfs->edges[i].lt != v) && ( dfs->edges[i].rt != v) )
				continue;
		/*! OK, next edge containing v found; get y -- current neighbour  of v */
		if ( v == dfs->edges[i].lt )	y = dfs->edges[i].rt;
		else							y = dfs->edges[i].lt;
		
		if ( dfs->discovered[y] != 0)	/*! Is y already discovered? */
			continue;

		dfs->parent[y] = v;
		dfs->discovered[y] = 1;
		dfs->passed++;
		ids[dfs->passed-1]	= v;
		ids[dfs->passed]	= y;

		if ( y == dfs->end && y > 0 )	/*! Are we at the end? */
		{
			printf("\n\tPath found: ");
			for (i=0; i<dfs->passed; i++)	printf("%-d ", ids[i]);
			printf("\n");
			dfs->discovered[y] = 0;
			dfs->passed--;
			break;
		}
	}

	for (i=0; i<dfs->ne; i++)
	{
		if ( (dfs->edges[i].lt != v) && ( dfs->edges[i].rt != v) )
			continue;
		if ( v == dfs->edges[i].lt )	
			y = dfs->edges[i].rt;
		else
			y = dfs->edges[i].lt;
		if ( dfs->discovered[y] != 0)	
			continue;
		if ( y == dfs->end && y > 0 )
			continue;

		dfs->discovered[y] = 1;
		dfs->passed++;
		ids[dfs->passed-1]	= v;
		ids[dfs->passed]	= y;

		dfs_run( dfs, y, ids );

		dfs->discovered[y] = 0;
		dfs->passed--;

	}
#if 0
	/*! Mark this node as processed*/
	/*ids.push_back(v);*/
	dfs->passed = dfs->passed + 1;
	ids[dfs->passed-1] = v;
	dfs->processed[v] = 1;
	/*printf ("*%-d*\n", v);*/
#endif
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
int start=-1;



	printf("Testing C light_dfs code (for getting connected components, etc. )\n");

	{
		int i, j, nn, ne;
		EDGE *e = NULL;
		DFSEARCH *dfs=NULL;
		int *ids = NULL;


		e = (EDGE *) calloc( 1000, sizeof(EDGE) );
		if ( !e )
			return -1;
		
		
		/*************************************************************/
		
		nn = 9;
		ne = 8;

		e[0].lt = 1; e[0].rt = 2; 
		e[1].lt = 2; e[1].rt = 3; 
		/*e[1].lt = -1; e[1].rt = -1;*/ 
		e[2].lt = 3; e[2].rt = 4; 
		e[3].lt = 4; e[3].rt = 5; 
		e[4].lt = 4; e[4].rt = 6; 
		
		e[5].lt = 2; e[5].rt = 7; 
		e[6].lt = 3; e[6].rt = 7; 

		e[7].lt = 8; e[7].rt = 9; 
		
		/***********************************************************


								  7
								 / \
							1---2---3---4---5    8---9
										 \
										  6


		***********************************************************/



		printf("Edges:\n");
		for (j=0; j<ne; j++)
			printf("(%-d, %-d) ", e[j].lt, e[j].rt);
		printf("\n");

		/* Just DFS traverse */

		dfs = dfs_new( nn, ne, e );
		if ( !dfs )
			return -1;

		ids = (int *) calloc( nn+1, sizeof(int) );
		if ( !ids ) 
			return -1;
		for (i=0; i<nn; i++)
			ids[i] = -1;

		dfs_reset( dfs );
		printf("\nDFS traversal starting from (%-d)\n\tBonds discovered: ", 1 );
		dfs_run( dfs, 1, ids );
		printf("\n\tNodes discovered: ");
		for (i=0; i<nn, ids[i]>0; i++)
			printf("%-d ", ids[i]);
		
		dfs_reset( dfs );
		for (i=0; i<nn; i++)
			ids[i] = -1;
		printf("\nDFS traversal starting from (%-d)\n\tBonds discovered: ", 4 );
		dfs_run( dfs, 4, ids );	
		printf("\n\tNodes discovered: ");
		for (i=0; i<nn, ids[i]>0; i++)
			printf("%-d ", ids[i]);

		dfs_reset( dfs );
		for (i=0; i<nn; i++)
			ids[i] = -1;
		printf("\nDFS traversal starting from (%-d)\n\tBonds discovered: ", 9 );
		dfs_run( dfs, 9, ids );	
		printf("\n\tNodes discovered: ");
		for (i=0; i<nn, ids[i]>0; i++)
			printf("%-d ", ids[i]);

		dfs_reset( dfs );
		for (i=0; i<nn; i++)
			ids[i] = -1;
		start = 2;
		dfs->end = 5;
		printf("\nDFS traversal starting from (%-d) and ending at (%-d)\n\tBonds discovered: ", start, dfs->end );
		dfs_run( dfs, start, ids );	
		printf("\n\tNodes discovered: ");
		for (i=0; i<nn, ids[i]>0; i++)
			printf("%-d ", ids[i]);
		


		/* Now find all paths between the two nodes */

		dfs->end = 5;
		dfs_reset( dfs );
		for (i=0; i<nn; i++)
			ids[i] = -1;
		//printf("\nDFS traversal starting from (%-d)\n\tBonds discovered: ", 9 );
		//dfs_run( dfs, 9, ids );	


		dfs_free( dfs );

	}


	return 0;
}
#if 0		


#if 0
    Matr A;
    const int Row0[] = { 0,1,0,1,0,0,0,1,0 };
    const int Row1[] = { 1,0,1,0,0,1,0,0,0 };
    const int Row2[] = { 0,1,0,1,1,0,1,0,0 };
    const int Row3[] = { 1,0,1,0,0,0,1,0,0 };
    const int Row4[] = { 0,0,1,0,0,0,0,1,1 };
    const int Row5[] = { 0,1,0,0,0,0,0,0,0 };
    const int Row6[] = { 0,0,1,1,0,0,0,0,0 };
    const int Row7[] = { 1,0,0,0,1,0,0,0,0 };
    const int Row8[] = { 0,0,0,0,1,0,0,0,0 };
    int n = sizeof(Row0)/sizeof(int);
    A.push_back ( VecInt(Row0, Row0 + n ) );
    A.push_back ( VecInt(Row1, Row1 + n ) );
    A.push_back ( VecInt(Row2, Row2 + n ) );
    A.push_back ( VecInt(Row3, Row3 + n ) );
    A.push_back ( VecInt(Row4, Row4 + n ) );
    A.push_back ( VecInt(Row5, Row5 + n ) );
    A.push_back ( VecInt(Row6, Row6 + n ) );
    A.push_back ( VecInt(Row7, Row7 + n ) );
    A.push_back ( VecInt(Row8, Row8 + n ) );


    VecInt R;
    start = 5;
    zdfs(A, start, R);  //! Find spanning tree for G1.
    int j = 6;          //! Check for some simple path (start-j).
    do
    { 
        printf("%d, ",j); 
        j=R[j]; 
    }  while ( j < n );

    start = 4;
    printf("\nPaths from %d\n", start);
    zdfs_paths_matr( A, start );
#endif




#if 0
    //! G1 example.
    BondsData G1;
    G1.push_back( bond_(0,1, 1) );
    G1.push_back( bond_(0,3, 1) );
    
    G1.push_back( bond_(0,7, 1) );
    G1.push_back( bond_(1,5, 1) );
    G1.push_back( bond_(1,2, 1) );
    G1.push_back( bond_(2,4, 1) );
    G1.push_back( bond_(2,6, 1) );
    G1.push_back( bond_(2,3, 1) );
    G1.push_back( bond_(3,6, 1) );
    G1.push_back( bond_(4,7, 1) );
    G1.push_back( bond_(4,8, 1) );

    start = 4;
    printf("G1 example. Paths from %d\n", start);
    zdfs_paths( G1, start);


    //! REC1922-good_igor.sdf example.
    BondsData REC1922;
    REC1922.push_back( bond_(1,3, 1) );
    REC1922.push_back( bond_(3,4, 1) );   
    REC1922.push_back( bond_(4,5, 2) );
    REC1922.push_back( bond_(5,6, 1) );
    REC1922.push_back( bond_(6,7, 1) );
    REC1922.push_back( bond_(7,8, 1) );
    REC1922.push_back( bond_(8,9, 2) );
    REC1922.push_back( bond_(9,10, 1) );
    REC1922.push_back( bond_(10,11, 2) );
    REC1922.push_back( bond_(11,12, 1) );
    REC1922.push_back( bond_(12,13, 1) );
    REC1922.push_back( bond_(13,14, 2) );
    REC1922.push_back( bond_(14,15, 1) );
    REC1922.push_back( bond_(15,16, 1) );
    REC1922.push_back( bond_(16,17, 1) );
    REC1922.push_back( bond_(17,18, 1) );
    REC1922.push_back( bond_(18,19, 1) );
    REC1922.push_back( bond_(20,19, 1) );
    REC1922.push_back( bond_(20,21, 1) );
    REC1922.push_back( bond_(21,22, 2) );
    REC1922.push_back( bond_(21,23, 1) );
    REC1922.push_back( bond_(23,2, 1) );

    start = 21;
    printf("REC1922-good_igor. Paths from %d\n", start);
    zdfs_paths( REC1922, start);


    //! REC17-good_igor.sdf example.
    BondsData REC17;
    REC17.push_back( bond_(1,3, 1) );
    REC17.push_back( bond_(1,2, 1) );   
    REC17.push_back( bond_(2,4, 1) );
    REC17.push_back( bond_(3,6, 1) );
    REC17.push_back( bond_(3,5, 1) );
    REC17.push_back( bond_(4,2, 1) );
    REC17.push_back( bond_(4,5, 1) );
    REC17.push_back( bond_(4,7, 2) );
    REC17.push_back( bond_(5,8, 1) );
    REC17.push_back( bond_(5,9, 1) );
    REC17.push_back( bond_(7,10, 1) );
    REC17.push_back( bond_(7,11, 1) );
    REC17.push_back( bond_(8,13, 1) );
    REC17.push_back( bond_(10,12, 1) );
    REC17.push_back( bond_(12,13, 1) );
    REC17.push_back( bond_(13,14, 1) );
    REC17.push_back( bond_(14,15, 1) );
    REC17.push_back( bond_(14,16, 2) );

    start = 5;
    printf("REC17-good_igor. Paths from %d\n", start);
    zdfs_paths( REC17, start);
#if 0
	printf("\nREC17-good_igor. Search for all paths from all verteces.\n");
	for (start=1; start <= 16; start++)
	{
		printf("%-d\n", start);
		zdfs_paths( REC17, start);

	}
	printf("\nComplete.");
#endif


	BondsData C60;
	C60.push_back( bond_( 1,  2, 2 ) );
    C60.push_back( bond_( 1, 3, 1 ) );
    C60.push_back( bond_( 1, 4, 1 ) );
    C60.push_back( bond_( 2, 5, 1 ) );
    C60.push_back( bond_( 2, 6, 1 ) );
    C60.push_back( bond_( 3, 7, 2 ) );
    C60.push_back( bond_( 3, 8, 1 ) );
    C60.push_back( bond_( 4, 9, 2 ) );
    C60.push_back( bond_( 4, 10, 1 ) );
    C60.push_back( bond_( 5, 10, 1 ) );
    C60.push_back( bond_( 5, 11, 2 ) );
    C60.push_back( bond_( 6, 12, 2 ) );
    C60.push_back( bond_( 6, 13, 1 ) );
    C60.push_back( bond_( 7, 14, 1 ) );
    C60.push_back( bond_( 7, 15, 1 ) );
    C60.push_back( bond_( 8, 13, 1 ) );
    C60.push_back( bond_( 8, 16, 2 ) );
    C60.push_back( bond_( 9, 14, 1 ) );
    C60.push_back( bond_( 9, 17, 1 ) );
    C60.push_back( bond_( 10, 18, 2 ) );
    C60.push_back( bond_( 11, 19, 1 ) );
    C60.push_back( bond_( 11, 20, 1 ) );
    C60.push_back( bond_( 12, 19, 1 ) );
    C60.push_back( bond_( 12, 21, 1 ) );
    C60.push_back( bond_( 13, 22, 2 ) );
    C60.push_back( bond_( 14, 23, 2 ) );
    C60.push_back( bond_( 15, 16, 1 ) );
    C60.push_back( bond_( 15, 24, 2 ) );
    C60.push_back( bond_( 16, 25, 1 ) );
    C60.push_back( bond_( 17, 26, 2 ) );
    C60.push_back( bond_( 17, 27, 1 ) );
    C60.push_back( bond_( 18, 27, 1 ) );
    C60.push_back( bond_( 18, 28, 1 ) );
    C60.push_back( bond_( 19, 29, 2 ) );
    C60.push_back( bond_( 20, 28, 1 ) );
    C60.push_back( bond_( 20, 30, 2 ) );
    C60.push_back( bond_( 21, 22, 1 ) );
    C60.push_back( bond_( 21, 31, 2 ) );
    C60.push_back( bond_( 22, 32, 1 ) );
    C60.push_back( bond_( 23, 26, 1 ) );
    C60.push_back( bond_( 23, 33, 1 ) );
    C60.push_back( bond_( 24, 33, 1 ) );
    C60.push_back( bond_( 24, 34, 1 ) );
    C60.push_back( bond_( 25, 32, 2 ) );
    C60.push_back( bond_( 25, 35, 1 ) );
    C60.push_back( bond_( 26, 36, 1 ) );
    C60.push_back( bond_( 27, 37, 2 ) );
    C60.push_back( bond_( 28, 38, 2 ) );
    C60.push_back( bond_( 29, 30, 1 ) );
    C60.push_back( bond_( 29, 39, 1 ) );
    C60.push_back( bond_( 30, 40, 1 ) );
    C60.push_back( bond_( 31, 39, 1 ) );
    C60.push_back( bond_( 31, 41, 1 ) );
    C60.push_back( bond_( 32, 42, 1 ) );
    C60.push_back( bond_( 33, 43, 2 ) );
    C60.push_back( bond_( 34, 35, 2 ) );
    C60.push_back( bond_( 34, 44, 1 ) );
    C60.push_back( bond_( 35, 45, 1 ) );
    C60.push_back( bond_( 36, 46, 2 ) );
    C60.push_back( bond_( 36, 47, 1 ) );
    C60.push_back( bond_( 37, 38, 1 ) );
    C60.push_back( bond_( 37, 46, 1 ) );
    C60.push_back( bond_( 38, 48, 1 ) );
    C60.push_back( bond_( 39, 49, 2 ) );
    C60.push_back( bond_( 40, 48, 2 ) );
    C60.push_back( bond_( 40, 50, 1 ) );
    C60.push_back( bond_( 41, 42, 2 ) );
    C60.push_back( bond_( 41, 51, 1 ) );
    C60.push_back( bond_( 42, 45, 1 ) );
    C60.push_back( bond_( 43, 44, 1 ) );
    C60.push_back( bond_( 43, 47, 1 ) );
    C60.push_back( bond_( 44, 52, 2 ) );
    C60.push_back( bond_( 45, 53, 2 ) );
    C60.push_back( bond_( 46, 54, 1 ) );
    C60.push_back( bond_( 47, 55, 2 ) );
    C60.push_back( bond_( 48, 56, 1 ) );
    C60.push_back( bond_( 49, 50, 1 ) );
    C60.push_back( bond_( 49, 51, 1 ) );
    C60.push_back( bond_( 50, 57, 2 ) );
    C60.push_back( bond_( 51, 58, 2 ) );
    C60.push_back( bond_( 52, 53, 1 ) );
    C60.push_back( bond_( 52, 59, 1 ) );
    C60.push_back( bond_( 53, 58, 1 ) );
    C60.push_back( bond_( 54, 55, 1 ) );
    C60.push_back( bond_( 54, 56, 2 ) );
    C60.push_back( bond_( 55, 59, 1 ) );
    C60.push_back( bond_( 56, 57, 1 ) );
    C60.push_back( bond_( 57, 60, 1 ) );
    C60.push_back( bond_( 58, 60, 1 ) );
    C60.push_back( bond_( 59, 60, 2 ) );
#endif



	BondsData test4zdfs;
    test4zdfs.push_back( bond_( 1, 2, 1 ) );
    test4zdfs.push_back( bond_( 1, 4, 1 ) );
    test4zdfs.push_back( bond_( 1, 5, 1 ) );
    test4zdfs.push_back( bond_( 2, 3,  2 ) );
    test4zdfs.push_back( bond_( 4, 6, 1 ) );
    test4zdfs.push_back( bond_( 4, 7, 1 ) );
    test4zdfs.push_back( bond_( 8, 2, 1 ) );
    test4zdfs.push_back( bond_( 10, 9, 1 ) );
    test4zdfs.push_back( bond_( 11, 9, 1 ) );
     test4zdfs.push_back( bond_( 12,10, 1 ) );
    test4zdfs.push_back( bond_( 13,11, 1 ) );
    test4zdfs.push_back( bond_( 13,12, 1 ) );
    test4zdfs.push_back( bond_( 8, 9, 1 ) );
    test4zdfs.push_back( bond_( 15,14, 1 ) );
    test4zdfs.push_back( bond_( 16,14, 1 ) );
    test4zdfs.push_back( bond_( 17,15,  2 ) );
    test4zdfs.push_back( bond_( 18,16, 1 ) );
    test4zdfs.push_back( bond_( 8,14, 1 ) );
    test4zdfs.push_back( bond_( 19,17, 1 ) );
    test4zdfs.push_back( bond_( 18,17, 1 ) );
    test4zdfs.push_back( bond_( 20,19, 1 ) );
    test4zdfs.push_back( bond_( 21,18, 1 ) );
    test4zdfs.push_back( bond_( 22,20, 1 ) );
    test4zdfs.push_back( bond_( 22,21, 1 ) );
    test4zdfs.push_back( bond_( 22,23, 1 ) );
    test4zdfs.push_back( bond_( 22,24, 1 ) );
    test4zdfs.push_back( bond_( 24,23, 1 ) );

	{
		start = 6;
		int maxlen = 4;
		int maxpaths = 32000;
		printf("    test4zdfs. Paths from %d\n", start);
		printf("\n	zdfs_paths_all\n");
		zdfs_paths_all( test4zdfs, start, maxlen, maxpaths );
		printf("\n\n	czdfs_paths_all\n");
		czdfs_paths_all( 27, test4zdfs, start, maxlen, maxpaths );
	}


    return 1;
}


///////////////////////////////////////////////////////////////////////////////
//! Just visit all the vertexes.
void zdfs( Matr& A, int X, VecInt& R)
{
bool c; 
int j,k,L;


    int n = A.size();
    
    
    VecInt St; 
    St.assign(n, 0);
    
    k = 0;      //! 'ê' points to the top of stack.
    St[k] = X;  //! Put starting node to stack.
    
    R.assign(n, -1);
    R[X] = n;   //! Mark X node as visited.
                //  -1 not visited,
                //  num>0 means visited and has parent 'num'.
    j = -1;

    do
    {
        L = St[k]; //! Current node L goes from stack.
        c = false;
        //! Loop finding a suitable neighbor.
        do
        {                       
            j++;
            if ( j >= n ) c = true;
            else
                if ( ( A[L][j] != 0 ) && ( R[j]== -1 ) ) 
                    c = true;
        } while ( !c ); //! Either suitable neighbor found or L-th row exchausted.
        
        if ( j > n-1 )  //! Stepping back as L-th row is exchausted.
        { 
            j = L; 
            k--;    //! Move top of the stack.
        }
        else            //! Stepping forth (suitable neighbor found).
        {
            k++;
            St[k] = j;  //! Put the new node into stack.
            R[j] = L;   //! Mark node as visited and store the parent.
            j = -1; 
        }
    }
    while ( k>=0 );

    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//! Find all paths emitting from point numbered X (conn matrix version).
void zdfs_paths_matr( Matr& A, int X)
{
bool b, c; 
int j, k, L;
int npaths=0;

    int n = A.size();

    VecInt R;
    R.assign(n, 0);
    
    VecInt St; 
    St.assign(n, 0);
    
    k = 0;      //! 'ê' points to the top of stack.
    St[k] = X;  //! Put starting node to stack.

    R[X] = 1;   //! Mark X node as visited.
    j = -1;

    b = true;

    do
    {
        L = St[k]; //! Current node L goes from stack.
        c = false;
        //! Loop finding a suitable neighbor.
        do
        {         
            j++;
            if ( j >= n ) c = true;
            else
                if ( ( A[L][j] != 0 ) && ( R[j]== 0 ) ) 
                    c = true;
        } while ( !c ); //! Either suitable neighbor found or L-th row exchausted.
        
        if ( j > n-1 )  //! Stepping back as L-th row is exchausted.
        {
            if ( b ) //! If prev. step was "forth", output the chain.
            {
                npaths++;
#if 0
                printf("Path #%-d: ", npaths);
                    for (j=0; j<=k; j++)
                        printf("%d, ", St[j]); 
                    printf("\n");
#endif
                    b = false;
            }
            R[L] = 0; //! Going back from L, mark L as available once again.
            j = L;    //! This makes chains unique.
            k--;      //! Move top of the stack.
        }
        else            //! Stepping forth (suitable neighbor found).
        {
            b = true;
            k++;
            St[k] = j;  //! Put the new node into stack.
            R[j] = 1;   //! Specific feature.
            j = -1; 
        }
    }
    while ( k>=0 );

    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//! Find all paths emitting from point numbered X (list of bonds version).
void zdfs_paths( BondsData& BD, int X)
{
bool b, c; 
int j, k, L;
int npaths=0;

    int n = 0;
    int r;
    int nbonds = BD.size();
    Matr A;
    for (r=0; r<nbonds; r++)
    {
        if ( n < BD[r].id1 )
            n = BD[r].id1;
        if ( n < BD[r].id2 )
            n = BD[r].id2;
    }
    n++;

    VecInt dummy(n, 0);

    A.assign( n, dummy);

    for (r=0; r<nbonds; r++)
    {
        A[ BD[r].id2 ][ BD[r].id1 ] = BD[r].kind;
        A[ BD[r].id1 ][ BD[r].id2 ] = BD[r].kind;
    }

    VecInt R;
    R.assign(n, 0);
    
    VecInt St; 
    St.assign(n, 0);
    
    k = 0;      //! 'ê' points to the top of stack.
    St[k] = X;  //! Put starting node to stack.

    R[X] = 1;   //! Mark X node as visited.
    j = -1;

    b = true;

    do
    {

        L = St[k]; //! Current node L goes from stack.
        c = false;
        //! Loop finding a suitable neighbor.
        do
        {         
            j++;
            if ( j >= n ) c = true;
            else
                if ( ( A[L][j] != 0 ) && ( R[j]== 0 ) ) 
                    c = true;
        } while ( !c ); //! Either suitable neighbor found or L-th row exchausted.
        
        if ( j > n-1 )  //! Stepping back as L-th row is exchausted.
		//if ( ( j > n-1 ) || k >= maxlen-1 )
        {
            if ( b ) //! If prev. step was "forth", output the chain.
            {
                npaths++;

                printf("Path #%-d: \n", npaths);
				for (j=0; j<=k; j++)
                        printf("%d, ", St[j]); 
                    printf("\n");
                    b = false;
            }
            R[L] = 0; //! Going back from L, mark L as available once again.
            j = L;    //! This makes chains unique.
            k--;      //! Move top of the stack.
        }
        else            //! Stepping forth (suitable neighbor found).
        {
            b = true;
            k++;
            St[k] = j;  //! Put the new node into stack.
            R[j] = 1;   //! Specific feature.
            j = -1; 
        }
    }
    while ( k>=0 );

    return;
}



///////////////////////////////////////////////////////////////////////////////
//
//! Find all (but <= maxpaths) paths from node X which are not longer than maxlen.
//
//! This version finds paths but not simple paths: 
//  that is, it allows us to have cycles in paths.
//  Still, any edge in found path (bond) is traversed only once.

void zdfs_paths_all( BondsData& edges, int v0, int maxlen, int maxpaths)
{
bool b, c; 
int j, k, v;
int npaths=0;

    int n = 0;
    int r;
    int nbonds = edges.size();
    for (r=0; r<nbonds; r++)
    {
        if ( n < edges[r].id1 )
            n = edges[r].id1;
        if ( n < edges[r].id2 )
            n = edges[r].id2;
    }
    n++;

    Matr a;			// adjacency matrix
	Matr passed;	// passed[i]j] = 1 means that edge (i,j) has been visited. 
    VecInt nzeros(n, 0);
	passed.assign( n, nzeros );	// =1 edge visited. 
	a.assign( n, nzeros );
    for (r=0; r<nbonds; r++)
    {
        a[ edges[r].id2 ][ edges[r].id1 ] = edges[r].kind;
        a[ edges[r].id1 ][ edges[r].id2 ] = edges[r].kind;
    }

    VecInt stack; 
    stack.assign(n, 0);
    
    k = 0;      //! 'ê' points to the top of stack.
    stack[k] = v0;  //! Put starting node to stack.
    j = -1;

    b = true;

    do
    {
        v = stack[k]; //! Current node L goes from stack.
        c = false;
        //! Loop finding a suitable neighbor.
        do
        {         
            j++;
            if ( j >= n ) 
				c = true;
            else
                if ( a[v][j] && !passed[v][j] )
				{
                    c = true;
					// printf(" ..%d->%d passed=%-d ..", v, j, passed[v][j] );
				}
        } while ( !c ); //! Either suitable neighbor found or L-th row exchausted.
        
        //if ( j > n-1 )  //! Stepping back as v-th row is exchausted.
		if ( ( j > n-1 ) || k >= maxlen )
        {
            if ( b ) //! If prev. step was "forth", output the chain.
            {
                npaths++;

                printf("\nPath #%-d: \n", npaths);
				for (j=0; j<=k; j++)
					printf("%d, ", stack[j]); 
				// printf("\n\tForming new path:");
                b = false;
            }
            j = v;    //! This makes chains unique.
            k--;      //! Move top of the stack.
			//! Going back from v, mark edges of v as available once again.
			if ( k>=0 )
			{
				passed[v][stack[k]] = passed[stack[k]][v] = 0;
				// printf(" {%d,%d}..", v, stack[k]);
			}

        }
        else            //! Stepping forth (suitable neighbor found).
        {
            b = true;
            k++;
            stack[k] = j;  //! Put the new node into stack.
			passed[stack[k-1]][j] = passed[j][stack[k-1]] = 1;
			// printf(" (%d,%d)..", stack[k-1], j );
            j = -1; 
        }
    }
    while ( k>=0 && npaths < maxpaths);

    return;
}



#if 0
//! Collect connected components (not starting from forbidden_nodes).
int get_connected_components(vector< vector<int> >& components)
{
	int c=0;	// component number

	//! Initialize dfs internal data structs

	PMMolGraphDFS dfs(this);
	int i;

	for (i=0; i<dfs.nn; i++) 
	{
		//! Make DFS starting from each not-still-visited atomic node
		if (dfs.discovered[i] == FALSE) 
		{
			c = c+1;
			vector<int> ids;
			dfs.dfs(i,ids,forbidden_nodes);
			//dfs.dfs(i);
			components.push_back(ids);
			//printf("\nComponent %d: ",c);
			//for (int k=0;k<ids.size();k++)
			//	printf("%d ",ids[k]);	
			//printf("\n");
		}
	}

	return c;
}


#endif



/*
	edges is bonds as nbonds x 3 matrix ( bond[0, 1, 2] are {i, j, kind} )
*/
int  czdfs_paths_all( int nat, int nbonds, int **edges, int at0, int maxlen, int maxpaths)
{
int j, k, r, v;
int npaths=0, err;
int b, c;			/* boolean */
int *stack=NULL; 
int **a=NULL;		/* adjacency matrix nat x nat									*/
int **passed=NULL;	/* passed[i][j] = 1 means that the edge (i,j) has been visited.	*/


	err = 1;
	stack = (int *) calloc( nat, sizeof(int));			
	if ( !stack)
		goto exitf;
	if ( imat_new( nat, nat, &a ) )	
		goto exitf;
	if ( imat_new( nat, nat, &passed ) )	
		goto exitf;
	err = 0;

    for (r=0; r<nbonds; r++)
    {
		int at1 = edges[r][0];
		int at2 = edges[r][1];
        a[at2][at1] = a[at1][at2] = edges[r][2];
    }

    k = 0;			/* ê points to the top of stack */
    stack[k] = at0;  /* Put starting node to stack. */
    j = -1;
    b = 1;
	do
    {
        v = stack[k]; /* Current node goes from stack. */
        c = 0;
        do	/* Loop finding a suitable neighbor  */
        {         
            j++;
            if ( j >= nat ) 
				c = 1;
            else
                if ( a[v][j] && !passed[v][j] )
				{
                    c = 1;
					/* printf(" ..%d->%d passed=%-d ..", v, j, passed[v][j] ); */
				}
        } while ( !c ); /* Either suitable neighbor found or L-th row exchausted. */
        
        if ( ( j > nat-1 ) || k >= maxlen )	/*if ( j > n-1 )  ! Stepping back as v-th row is exchausted. */
        {
            if ( b ) /* If prev. step was "forth", output the chain. */
            {
                npaths++;
                printf("\nPath #%-d: \n", npaths);
				for (j=0; j<=k; j++)
					printf("%d, ", stack[j]); 
												/* printf("\n\tForming new path:"); */
                b = 0;
            }
            j = v;    /* This makes chains unique.	*/
            k--;      /* Move top of the stack. */
			/* Going back from v, mark edges of v as available once again. */
			if ( k>=0 )
			{
				passed[v][stack[k]] = passed[stack[k]][v] = 0;
				/* printf(" {%d,%d}..", v, stack[k]); */
			}

        }
        else            /* Stepping forth (suitable neighbor found). */
        {
            b = 1;
            k++;
            stack[k] = j;  /*! Put the new node into stack. */
			passed[stack[k-1]][j] = passed[j][stack[k-1]] = 1;
			/* printf(" (%d,%d)..", stack[k-1], j ); */
            j = -1; 
        }
    
	} while ( k>=0 && npaths < maxpaths);

exitf:
	if ( stack ) free( stack );
	imat_free( nat, a );
	imat_free( nat, passed );

    return err;
}

#endif
