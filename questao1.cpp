#include <bits/stdc++.h>
using namespace std;
/*
Implementacao do método ρ de Pollard:
    Utilize a funcao de iteracao: g(x)=(x2+1) mod Ni
    Semente – x0=2.
    Em cada iteracao, calcule: mdc ( x ∣ 2−x1∣,Ni) até encontrar um fator pi nao trivial de Ni
    O programa deve exibir cada passo da iteracao.

Observacao: O calculo do mdc deve ser feito utilizando o Algoritmo de Euclides, implementado
    pelo aluno (nao é permitido usar funcões prontas como std::gcd).

*/
void printName();
int MDC(int a, int b);
int MDC_SemPrint(int a, int b); 
int Pollard(int n); // Usa a função g(x) = ((x² + 1)mod(N)) e raiz X0 = 2
int expoentePublico(int z, int n);  // Formula para encontrar o 'e'
int expoentePrivado(int e, int z);  //                          'd'
vector<int> pre_Codificacao(string frase);  // Transforma as letras em codigo numerico de 2 casas
bool e_primo(int n);                        // retorna se e primo ou nao
int exp_mod(int m, int e, int n, int z);    // Escolhe qual metodo usar
int modexp(int base, int exp, int mod);     // Faz a exponenciacao modular
int Fermat(int a, int exp, int n);          // 1 dos 3 metodos escolhidos pelo exp_mod
int Euler(int a, int exp, int n, int z);    // 1 dos 3 metodos escolhidos pelo exp_mod
int Euclidiana(int a, int exp, int n);      // 1 dos 3 metodos escolhidos pelo exp_mod
char rev_pre_Codificacao(int x);            // Reverte os blocos de 2 digitos de volta para letras
int LerEntrada(const char *s){              // Le a entrada garantindo que N esta dentro das condicoes
    int N;
    while (true){
        cout << s << " = ";
        cin >> N;
        if (N < 100 || N > 9999){
            cout << "Valor invalido. Entre um numero entre 100 e 9999.\n";
            continue;
        }
        if (e_primo(N)){
            cout << N <<" eh primo. Entre um composto.\n";
            continue;
        }
        return N;
    }
}
//-------------------------------------------------------------

int main(){
    printName();

    cout << "Entre os valores de N1 e N2, eles devem ser produtos de primos *distintos* para que o metodo \"P de Polard\" seja eficiente.\n";
    
    int N1, N2, P, Q; // Vao de 100 a 999
        back:
        
    while(1){
        N1 = LerEntrada("N1");
        P = Pollard(N1);
        cout << "---------------------\n"<< "Pollard para " << N1 << " = " << P << '\n' << "---------------------\n";
        if(!e_primo(P)){
            cout << "P nao primo, escolha outro N1\n";
            continue;
        }
        break;
    }
    while(1){
        N2 = LerEntrada("N2");
        Q = Pollard(N2);
        cout << "---------------------\n"<< "Pollard para " << N2 << " = " << Q << '\n' << "---------------------\n";
        if(!e_primo(Q)){
            cout << "Q nao primo, escolha outro N2\n";
            continue;
        }
        break;
    }
    cout <<"\n-------------------------" <<       "\n     Pollard: P = " << P << "\n     Pollard: Q = " << Q << "\n-------------------------" << '\n';
    if(P == Q){
        cout << "Sua entrada gerou 2 numeros primos iguais\necolha outra entrada: \n";
        goto back;  // volta para a escolhe de N1 e N2
    }
    cout << "\n----------\nP = " << P << "\nQ = " << Q << "\n----------\n";

// Geracao de Chaves

    int n = P * Q;
    int z = (P-1)*(Q-1);
    int e = expoentePublico(z, n);
    int d = expoentePrivado(e, z);  

    // Etapa 3 - 
    // Criptografia:
    cout << "_____________________________________________\n";
    cout << "Chave Publica: (" << n << ',' << e << ")\n";
    cout << "Chave Privada: (" << n << ',' << d << ")\n";
    cout << "_____________________________________________\nEntre a frase que deseja codificar: \n";
    string frase;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, frase);

    vector<int> preCriptografado = pre_Codificacao(frase);
    vector<int> Criptografado;
    cout << "----------------------------\n";
    for(int i = 0; i < preCriptografado.size(); i++){
        (i+1 < preCriptografado.size())? cout << preCriptografado[i] << " - " : cout << preCriptografado[i] << '\n';
    }
    cout << "\n-----------------------------------------------\nCriptografia (por bloco de 2 digitos)\n";
    cout << "Usando a Chave Publica: (" << n << ',' << e << ")\n-----------------------------------------------\n";
    for(int i = 0; i < preCriptografado.size(); ++i){
        int m = preCriptografado[i];
        cout << "\nBloco " << i+1 << ": " << frase[i] << " --> " << m << '\n';
        int c = exp_mod(m, e, n, z);
        cout << "C = M^E mod N\n" << "C = " << c << '\n';
        Criptografado.push_back(c);
    }
    cout << "----------------------- \n";
    cout << "Mensagem criptografada: \n";
    for(int i = 0; i < Criptografado.size(); i++){
        (i+1 < Criptografado.size())? cout << Criptografado[i] << " - " : cout << Criptografado[i] << '\n';
    }
    cout << "----------------------- \n";

// _____________________________________________________________________________
    cout << "\n--------------------------\n";
    cout <<   "    Descriptografia\n";
    cout << "Usando a Chave Privada: (" << n << ',' << d << ")\n";
    cout << "--------------------------\n";
    vector<int> Descriptografado;
    for(int i = 0; i < Criptografado.size(); i++){
        cout << "\nBloco " << i+1 << ": " << Criptografado[i] << "\n" ;
        int x = exp_mod(Criptografado[i], d, n, z);
        cout << "M = C^D mod N\n" << "M = " << x << '\n';
        Descriptografado.push_back(x);
    }
    cout << "\n_____________________________\n" << "Codigo numerico:\n";
    for(int i = 0; i < Descriptografado.size(); i++){
        (i+1 < Descriptografado.size())? cout << Descriptografado[i] << " - " : cout << Descriptografado[i] << '\n';
    }

    cout << "\nAgora podemos comparar o valor de cada bloco na tabela:\n" ;
    string mensagemDescript;
    for(int x = 0; x < Descriptografado.size(); x++){
        char c = rev_pre_Codificacao(Descriptografado[x]);
        mensagemDescript.push_back(c);
        cout << Descriptografado[x] << " --> " << mensagemDescript[x] << '\n';
    }
    for(int i = 0; i <mensagemDescript.size(); i++){
        (i+1 <mensagemDescript.size())? cout <<mensagemDescript[i] << " - " : cout <<mensagemDescript[i] << '\n';
    }
    cout << "\n--------------------------------------\n" << 
              "     Frase Descriptografada:\n";
    cout << mensagemDescript;
    return 0;
}

//-------------------------------------------------------------
int Fermat(int a, int exp, int n) {
    cout << "[Teorema de Fermat]\n";
    cout << "Condicao: n e primo -> a^(n-1) ≡ 1 (mod n)\n";

    // Reduz expoente usando Fermat
    int exp_reduzido = exp % (n - 1);
    cout << "Reducao: " << exp << " mod (" << n << " - 1) = " << exp_reduzido << endl;

    int resultado = modexp(a, exp_reduzido, n);
    cout << "Resultado final: " << resultado << endl;
    return resultado;
}

int Euler(int a, int exp, int n, int z) {
    cout << "[Teorema de Euler]\n";
    cout << "Condicao: mdc(a, n) = 1 -> a^phi(n) === 1 (mod n)\n";

    // Reduz expoente usando φ(n)
    int exp_reduzido = exp % z;
    cout << "Reducao: " << exp << " mod phi(" << n << ") = " << exp_reduzido << endl;

    int resultado = modexp(a, exp_reduzido, n);
    cout << "Resultado final: " << resultado << endl;
    return resultado;
}

int Euclidiana(int a, int exp, int n) {
    cout << "[Reducao por Divisao Euclidiana]\n";
    cout << "Nao ha relacao especial, reduzimos o expoente diretamente.\n";

    int exp_reduzido = exp % n;
    cout << "Reducao: " << exp << " mod " << n << " = " << exp_reduzido << endl;

    int resultado = modexp(a, exp_reduzido, n);
    cout << "Resultado final: " << resultado << endl;
    return resultado;
}

int modexp(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {   // enquanto o expoente for > 0
        cout << "exp = " << exp << " | base = " << base << " | result = " << result << endl;
        if (exp % 2 == 1)   // Se for impar 
            result = (result * base) % mod;
        base = (base * base) % mod; // faz base² mod(n)
        exp /= 2;                   // reduz o expoente pela metade   
    }
    return result;
}         
int exp_mod(int m, int e, int n, int z){
    if (e_primo(n)){
        cout << "N = " << n << " e primo, usando Fermat";
        return Fermat(m, e, n);
    }
    else if (MDC_SemPrint(m, n) == 1){
        cout << "MDC(" << m << ',' << n << ") = 1, usando Euler\n";
        return Euler(m, e, n, z);
    }

    return Euclidiana(m, e, n);
}
bool e_primo(int n) {   // como o numero so vai ate 999, posso testar se ele é divisivel por 2, 3, 5, 7, ...
    if (n < 2)          // os numeros so precisam ir ate sqrt(n)
        return false;
    if (n % 2 == 0) 
        return (n == 2);
    for (int d = 3; d <= sqrt(n); d += 2)
        if (n % d == 0)
             return false;
    return true;
}
char rev_pre_Codificacao(int x){
    if(x > 10 && x < 37)
        return (x + 'a' - 11);
    else if(x == 90)
        return ' ';
    else if(x == 91)
        return ',';
    else if(x == 92)
        return'.';
    else if(x == 93)
        return ';';
    return '_';
}
vector<int> pre_Codificacao(string frase){ // Ele nao diferencia minuscula e maiuscula ainda
    cout << "----------------------------\n" << 
            "      Pre Codificacao\n";
    vector<int> codificado;
    for(int i = 0; i < frase.size(); i++){
        char caracter = frase[i];
        
        if(caracter >= 'a' && caracter <= 'z')
            codificado.push_back(11 + caracter - 'a');
        else if(caracter >= 'A' && caracter <= 'Z')
            codificado.push_back(11 + caracter - 'A');
        else if(caracter == ' '){
            codificado.push_back(90);
        }
        else if(caracter == ','){
        codificado.push_back(91);
        }
        else if(caracter == '.'){
        codificado.push_back(92);
        }
        else if(caracter == ';'){
        codificado.push_back(93);
        }
        else{
            cout << "Caracter " << caracter << " Invalido!\n";
            codificado.push_back(-99);
            return codificado;
        }
    }
    return codificado;
}
void printName(){
    cout << "______________________________\n|Matheus Pinheiro - 241025336\n|Gabriel Mota Oliveira - 241011081\n|_____________________________\n";
    return;
}
int MDC(int a_in, int b_in) {
    int a = abs(a_in), b = abs(b_in);
    cout << "  >> Calculando mdc(" << a << ", " << b << ") com Algoritmo de Euclides:\n";
    while (b != 0) {
        int q = a / b;
        int r = a % b;
        cout << "     " << a << " = " << q << " * " << b << " + " << r << "\n";
        a = b;
        b = r;
    }
    cout << "  => mdc = " << a << "\n\n";
    return a;
}

int Pollard(int n) {
    int G1 = 2, G2 = 2, d = 1, i = 1;
    while (d <= 1 || d == n) {
        G1 = ((G1 * G1) + 1) % n;          
        G2 = ((G2 * G2) + 1) % n;          
        G2 = ((G2 * G2) + 1) % n;          
        d = MDC(abs(G1 - G2), n);
        cout << "Pollard " << i << ": G1 = " << G1 << ", G2 = " << G2 << ", d = " << d << '\n';
        i++;
    }
    return d;
}


int expoentePublico(int z, int n){
    int e = 2;
    while(e < n && e < z){
        if(MDC(e, z) == 1)
            return e;
        e++;
    }
    return -1;
}

int expoentePrivado(int e, int z){
    int t = 0, novo_t = 1;
    int r = z, novo_r = e;

    while (novo_r != 0) {
        int quociente = r / novo_r;
        int temp = t;
        t = novo_t;
        novo_t = temp - quociente * novo_t;

        temp = r;
        r = novo_r;
        novo_r = temp - quociente * novo_r;
    }

    if (r > 1) {
        cout << "Nao existe inverso modular!\n";
        return -1;
    }
    if (t < 0)
        t += z;

    cout << "Expoente privado D encontrado: " << t << endl;
    return t;
}
int MDC_SemPrint(int a_in, int b_in) {
    int a = abs(a_in), b = abs(b_in);
    // cout << "  >> Calculando mdc(" << a << ", " << b << ") com Algoritmo de Euclides:\n";
    while (b != 0) {
        int q = a / b;
        int r = a % b;
        // cout << "     " << a << " = " << q << " * " << b << " + " << r << "\n";
        a = b;
        b = r;
    }
    // cout << "  => mdc = " << a << "\n\n";
    return a;
}
