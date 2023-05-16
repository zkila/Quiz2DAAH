#include <bits/stdc++.h>
using namespace std;

string codes[256];

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
 
void storeCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$') {
        if (root->data == '\n')
            codes[root->data] = "\\n" + str;
        else
            codes[root->data] = str;
    }
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
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
    storeCodes(minHeap.top(), "");
}

void printCodes(string codes[], char arr[], int size)
{
    for (int i = 0; i < size; i++) {
        if (!codes[arr[i]].empty()) {
            if (arr[i] == '\n')
                cout << "\\n" << ": " << codes[arr[i]] << endl;
            else
                cout << arr[i] << ": " << codes[arr[i]] << endl;
        }
    }
}
 
int main(int argc, char* argv[])
{
	char arr[256]="";
	int freq[256]={0};
	int size=0;
    char filename[100] = "";
    FILE *fp;
    char ch;
    char copy[1000] = "";
    int i = 0;

	if(argc != 2 || (argv[1][1] != 'f' && argv[1][1] != 's')) {
        printf("Argument tidak valid\nCara execute: ./lukisan -[a/b]\n");
        exit(0);
    }
    if (strcmp(argv[1], "-f") == 0) {
        cout << "Masukkan";
        *fp = fopen(filename, "r");

        //memasukkan tiap karakter yang dibaca (dari txt) ke string
        while ((ch = fgetc(fp)) != EOF){
            copy[i]=ch;
            i++;
        }
        fclose(fp);
    }    
    else if (strcmp(argv[1], "-s") == 0) {
        cin >> inp;
    }
    


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

    cout<<"sebelum decode : "<<endl;
	cout<<copy<<endl;
    cout<<endl<<"karakter unik : "<<endl;
	// cout<<arr<<endl;
    for(int i = 0;i < size;i++){
        cout<<arr[i]<<" ";
    }

    cout<<endl<<endl<<"frekuensi : "<<endl;
    for(int i = 0;i < size;i++){
        cout<<freq[i]<<" ";
    }
    cout<<endl<<endl<<"alokasi bit setiap karakter : "<<endl;
	HuffmanCodes(arr, freq, size);
    printCodes(codes, arr, size);

    string res = "";

    cout<<endl<<"hasil encode :"<<endl;

    for(int i = 0;i < strlen(copy);i++){
        for(int j = 0;j < strlen(arr);j++){
            if(copy[i]==arr[j]) {
                res.append(codes[arr[j]]);
                break;
            }
        }
    }

    cout<<res<<endl;

    cout<<endl<<"bit sebelum : "<<strlen(copy)*8<<endl;
    cout<<"bit sesudah : "<<res.length()<<endl;

    return 0;
}
