int main(){
    int a;
    int r=1;
    scanf("%d",&a);
    for(int i =1;i<=a;i++){
        r *= i;
    }
    printf("%d\n",r);
}