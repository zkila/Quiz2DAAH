#include <bits/stdc++.h>
using namespace std;

string codes[256];

//struct yang merepresentasikan huffman tree
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

//struct yang digunakan untuk membandingkan minheapnode dengan minheapnode yang lain
//dapat dimanfaatkan oleh priority queue
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
//fungsi untuk menyimpan kode ke dalam string
void storeCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$') {
            codes[root->data] = str;
    }
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

//fungsi yang digunakan untuk menyelesaikan huffman tree
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

//fungsi yang digunakan untuk print kode yang telah disimpan
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
    char arr[256] = "";
    char filename[100] = "";
    char copy[1000] = "";
    int freq[256] = {0};
    int size = 0;
    char ch;
    FILE *fp;    
    
    int i = 0;

    //error (panduan argumen cmd)
    if(argc != 2 || (argv[1][1] != 'f' && argv[1][1] != 's')) {
        printf("Argument tidak valid\nCara execute: ./huffman -[f/s]\n");
        exit(0);
    }

    //mendapatkan input teks yang akan diencode
    if (strcmp(argv[1], "-f") == 0) {
        cout << "Masukkan nama file dengan tipe txt (contoh \"file.txt\"): " << endl;
        cin >> filename;
        fp = fopen(filename, "r");

        //memasukkan tiap karakter yang dibaca (dari .txt) ke string
        while ((ch = fgetc(fp)) != EOF){
            copy[i] = ch;
            i++;
        }
        fclose(fp);
    }    
    else if (strcmp(argv[1], "-s") == 0) {
        cout<<"Masukkan teks yang ingin diencode: " << endl;
        scanf("%[^\n]s", copy);
    }
    
    //mengubah setiap huruf alfabet menjadi kapital untuk memudahkan
    for(int i = 0; i < strlen(copy); i++){
        if(copy[i] >= 97 && copy[i] <= 122){
            copy[i] -= 32;
        }
    }
	
    //menghitung frekuensi tiap karakter yang muncul
    char curr;
    int n = 0;
    int j, l;
    for(l = 0; l < strlen(copy); l++){
		// curr=copy[l];
		for(j = 0; j < n; j++){
			if(arr[j] == copy[l]){
				freq[j]++;
				break;
			}
		}
		if(j == n){
			arr[n++] = copy[l];
			freq[j]++;
			size++;
		}
	}

    cout << "sebelum decode : " << endl;
    cout << copy << endl;
    cout << endl << "karakter unik : " << endl;

    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }

    cout << endl << endl << "frekuensi : " << endl;
    for(int i = 0; i < size; i++){
        cout << freq[i] << " ";
    }
    cout << endl << endl << "alokasi bit setiap karakter : " << endl;

    HuffmanCodes(arr, freq, size);
    printCodes(codes, arr, size);

    string res = "";

    cout << endl << "hasil encode :" << endl;

    for(int i = 0; i < strlen(copy); i++){
        for(int j = 0; j < strlen(arr); j++){
            if(copy[i] == arr[j]) {
                res.append(codes[arr[j]]);
                break;
            }
        }
    }
    //output encoded teks
    cout << res << endl;

    //perbandingan bit
    cout << endl << "bit sebelum : " << strlen(copy) * 8 << endl;
    cout << "bit sesudah : " << res.length() << endl;

    return 0;
}
