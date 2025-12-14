#include "iostream"
#include "vector"
#include "string"

bool IsPowerOfTwo(int a){
    if(a == 0){
        return false;
    }
    int powers = 1;
    while(powers <= a){
        if(powers == a){
            return true;
        }
        powers <<= 1;
    }
    return false;
}

int GetR(int n) {
    int r = 0;
    while ((1 << r) < n + 1){
        r++;
    }
    return r;
}

std::string Encode(int m, int n, std::string& data){
    std::vector<int> encoded(n + 1, 0);
    int r = GetR(n);
    if(m+r != n){
        return std::string("error m + r != n");
    }
    int data_i = 0;
    for(int i = 1; i <=n; i++){
        if(!IsPowerOfTwo(i)){
            encoded[i] = data[data_i] - '0';
            data_i++;
        }
    }
    for(int i = 1; i <= n; i <<= 1){
        for(int j = i; j <=n; j++){
            if(i & j){
                encoded[i] ^= encoded[j];
            }
        }
    }

    std::string res;
    for(int i = 1; i <= n;i++){
        res.push_back(char(encoded[i] + '0'));
    }
    return res;
}

int GetSyndrome(const std::vector<int>& code, int n){
    int res = 0;
    for (int i = 1; i <= n; i <<= 1) {
        int parity = 0;
        for(int j = i; j <=n; j++){
            if(i & j){
                parity ^= code[j]; 
            }
        }
        if(parity){
            res += i;
        }
    }
    return res;

}

std::string Decode(int n, std::string& coded_str, int& r_output){
    std::vector<int> coded(n + 1);
    for (int i = 1; i <= n; i++){
        coded[i] = coded_str[i - 1] - '0';
    }
    r_output = GetR(n);
    int syndrome = GetSyndrome(coded,n);
    if (syndrome >= 1 && syndrome <= n){
        coded[syndrome] ^= 1;
    }
    std::string data;
    for (int i = 1; i <= n; i++){
        if(!IsPowerOfTwo(i)){
            data.push_back(coded[i] + '0');
        }
    }
    return data;
}

bool IsValid(int n, std::string& coded_str){
    std::vector<int> coded(n+1);
    for (int i = 1; i <= n; i++){
        coded[i] = coded_str[i-1] - '0';
    }
    return GetSyndrome(coded,n) == 0;

}

int main(int argc, char** argv){
    if(argc == 1){
        return 0;
    }
    std::string command = argv[1];
    if(command == "encode"){
        int m = std::stoi(argv[2]);
        int n = std::stoi(argv[3]);
        std::string data = argv[4];
        
        std::cout << Encode(m,n,data) << '\n';

    } else if (command == "decode") {
        int n = std::stoi(argv[2]);
        std::string coded_str = argv[3];
        int r;
        std::string data = Decode(n, coded_str, r);

        std::cout << r << "\n";
        std::cout << data << "\n";
    }else if (command == "is_valid") {
        int n = std::stoi(argv[2]);
        std::string coded_str = argv[3];

        if(IsValid(n,coded_str)){
            std::cout << "1\n";
        }else{
            std::cout << "0\n";
        }
    }
    return 0;
}

