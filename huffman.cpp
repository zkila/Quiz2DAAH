#include <bits/stdc++.h>
using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$'){
        if(root->data == '\n') cout << "\\n" << ": " << str << "\n";
	    else cout << root->data << ": " << str << "\n";
    }
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    printCodes(minHeap.top(), "");
}
 
int main()
{
	char arr[256]="";
	int freq[256]={0};
	int size=0;

	  	
	char filename[100] = "input.txt";
    FILE *fp = fopen(filename, "r");

    char ch;
    char copy[1000]="";
    int i=0;
    //memasukkan tiap karakter yang dibaca (dari txt) ke string
    while ((ch = fgetc(fp)) != EOF){
		copy[i]=ch;
        i++;
    }
    fclose(fp);

    //mengubah setiap huruf alfabet menjadi kapital untuk memudahkan
	for(int i=0; i<strlen(copy); i++){
        if(copy[i]>=97 && copy[i]<=122){
            copy[i]-=32;
        }
    }
	
	char curr;
	int n=0,j,l;
	for(l = 0; l<strlen(copy);l++){
		// curr=copy[l];
		for(j = 0; j<n; j++){
			if(arr[j]==copy[l]){
				freq[j]++;
				break;
			}
		}
		if(j==n){
			arr[n++]=copy[l];
			freq[j]++;
			size++;
		}
	}

	cout<<copy<<endl;
	cout<<arr<<endl;
	printf("%d\n", freq[0]);

	HuffmanCodes(arr, freq, size);

    return 0;
}
