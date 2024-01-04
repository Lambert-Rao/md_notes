void bubble_sort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int a;
    int arr[n];
    for(int i = 0;i < n;++i)
    {scanf("%d",&a);
    arr[i]=a;}
    bubble_sort(arr,n);
    for(int i = 0;i < n;++i)
    {printf("%d\n",arr[i]);
    }
}
