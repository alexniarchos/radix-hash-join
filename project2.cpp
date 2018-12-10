#include "functions.h"

int main(void){
    relation **rels = NULL;
    int numofrels;
    numofbuckets=1;
    for(int i=0;i<n_last_digits;i++){
        numofbuckets*=2;
    }
    rels = init_relations(&numofrels);
    while(1){
        char* line=NULL;
        size_t len=0;
        vector<string*> results;
        int ret;
        while((ret=getline(&line, &len, stdin)) != -1){
            if(line[0]=='F')
                break;
            SQLquery* query=new SQLquery();
            query->parser(line);
            categoriser(query,rels,results);
            for(int i=0;i<query->predicates.size();i++)
                free(query->predicates[i]);
            for(int i=0;i<query->views.size();i++)
                free(query->views[i]);
            delete(query);
        }
        free(line);
        for(int i=0;i<results.size();i++){
            cout<<*results[i];
            delete results[i];
        }
        if(ret==-1)
            break;
    }
    for(int i=0;i<numofrels;i++){
        free(rels[i]->cols);
        free(rels[i]);
    }
    free(rels);
}