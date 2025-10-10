#include <stdio.h>
#define MAX 10

int n, m, trans[MAX][MAX], final[MAX], mark[MAX][MAX];

int main() {
    printf("States & inputs: "); scanf("%d %d", &n, &m);
    printf("Transition table:\n");
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) scanf("%d",&trans[i][j]);

    int f; printf("No. of final states: "); scanf("%d",&f);
    printf("Final states: ");
    for(int i=0;i<f;i++){int x; scanf("%d",&x); final[x]=1; }

    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++)
        if(final[i]!=final[j]) mark[i][j]=1;

    int changed;
    do {
        changed=0;
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
            if(mark[i][j]) continue;
            for(int k=0;k<m;k++){
                int a=trans[i][k], b=trans[j][k];
                if(a>b){int t=a;a=b;b=t;}
                if(mark[a][b]){mark[i][j]=1; changed=1; break;}
            }
        }
    } while(changed);

    int rep[MAX]; for(int i=0;i<n;i++) rep[i]=i;
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) if(!mark[i][j]) rep[j]=rep[i];

    printf("\nState sets of minimized DFA:\n");
    for(int i=0;i<n;i++){
        if(rep[i]!=i) continue;
        printf("State %d: ",i);
        printf("{ ");
        for(int j=0;j<n;j++) if(rep[j]==i) printf("%d ",j);
        printf("}\n");
    }

    printf("\nMinimized DFA:\nState\t"); for(int i=0;i<m;i++) printf("%d\t",i); printf("\n");
    for(int i=0;i<n;i++){ 
        if(rep[i]!=i) continue;
        printf("%d\t",i);
        for(int j=0;j<m;j++) printf("%d\t",rep[trans[i][j]]); 
        printf("\n");
    }
}