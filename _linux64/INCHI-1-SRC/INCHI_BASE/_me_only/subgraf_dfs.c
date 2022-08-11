/****************************************************************/
/****************************************************************/

typedef struct tagEdge
{
    int lt;
    int rt;
    int type;
} EDGE;


typedef struct subgraf_dfs
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
    /* Hook function */
    int		(*treat_node)(int);
    /* Hook function */
    int		(*treat_edge)(int,int);
} subgraf_dfs;


subgraf_dfs * subgraf_dfs_new(int nn, int ne, EDGE *e );
void subgraf_dfs_free( subgraf_dfs *dfs );
void subgraf_dfs_reset( subgraf_dfs *dfs );
void subgraf_dfs_run(subgraf_dfs *dfs, int v, int* ids);


/* */
subgraf_dfs *subgraf_dfs_new(int nn, int ne, EDGE *e )
{
subgraf_dfs *dfs = NULL; 

	dfs = (subgraf_dfs *) calloc(1, sizeof(subgraf_dfs));
	if ( !dfs )
		return NULL;
	
	dfs->nn		= nn;
	dfs->ne		= ne;
	dfs->edges	= e;
	
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

	subgraf_dfs_reset( dfs );
	
	return dfs;
}
void subgraf_dfs_reset( subgraf_dfs *dfs )
{
int i;
	for (i=0; i<dfs->nn+1; i++) 
	{
		dfs->processed[i] = dfs->discovered[i] = 0;
		dfs->parent[i] = -1;
	}
	dfs->completed = dfs->passed = 0;
}
void subgraf_dfs_free( subgraf_dfs *dfs )
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
void subgraf_dfs_run(subgraf_dfs *dfs, int v, int* ids)
{
    int i;

    dfs->discovered[v] = 1;
    for (i=0; i<dfs->ne; i++)
    {
        int y, id1, id2;
        id1 = dfs->edges[i].lt;
        id2 = dfs->edges[i].rt;
        if ( (id1!=v) && (id2!=v) )
            continue;
        if (id1==v)
            y = id2;
        else
            y = id1;
        if ( dfs->discovered[y] == 0) 
        {
            dfs->parent[y] = v;
            subgraf_dfs_run( dfs, y, ids );
        } 
    }
    
    dfs->passed = dfs->passed + 1;
    ids[dfs->passed-1] = v;
    dfs->processed[v] = 1;
}

