#include<stdio.h>
#include<string.h>

int main(){
    int i,j,k,m,n,cl;
    char a[100],b[100],c[200];
    printf("Enter the Polynomials: ");
    scanf("%s", a);
    printf("Enter the frame(data): ");
    scanf("%s", b);
    n = strlen(a);
    m = strlen(b);
    for(i=0;i<m;i++){
        if(a[i]=='1'){
            m=n-i;
            break;
        }
    }
    for(k=0;k<m;k++){
        a[k]=a[k+1];
    }
    cl = m+n-1;
    for(i=0;i<n;i++){
        c[i]=b[i];
    }
    for(i=n;i<cl;i++){
        c[i]='\0';
    }
    for(i=0;i<n;i++){
        if(c[i]=='1'){
            for(j=1,k=0;k<m;k++,j++){
                c[j]=(a[k]==c[j])?'0':'1';
            }
            
        }
    }
    for(i=0;i<n;i++){
        c[i] = b[i];
    }
    printf("\nThe message to be sent is: %s\n", c);
    return 0;
}