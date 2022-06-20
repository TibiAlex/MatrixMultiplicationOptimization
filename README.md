# MatrixMultiplicationOptimization
Optimized matrix multiplication in 2 ways, once with blas functions and once with cashing and pointer access optimization.

Buzera Tiberiu 333CA

# Enunt:

    Se dă următoarea operație cu matrice: C=B×A×At+Bt×B.

    -> A si B sunt matrice patratice de double de dimensiune N x N.
    -> A este o matrice superior triunghiulara
    -> At este transpusa lui A si Bt este transpusa lui B
    -> × este operația de înmulțire
    -> + este operatia de adunare

# Rulare si testare

    Pentru testarea temei se va apela comada make care va crea 3 executabile, tema2_blas, tema2_neopt si tema2_opt_m.

    Pentru rularea lor se vor apela comanda:
    ./tema2_<tipul> input, unde input este fișierul ce contine descrierea testelor.

    Pentru compararea rezultatelor se apeleaza comanda:
    .compare out_ref out time_difference

## solver_blas.c

    Pentru rezolvarea operatiilor pe matrici am inclus biblioteca "cblas.h" din care am folosit functiile cblas_dgemm pentru inmultire intre matrici (functie care tine cont daca trebuie folosite transpusele matricilor sau nu) si cblas_dtrmm pentru inmultire intre matrici (care tine cont de faptul ca una dintre matrici este superior triunghulara si calculeaza rezultatul in cealalta matrice).

## solver_neopt.c

    Pentru rezolvarea inmultirii de matrici am folosit algoritmul neoptimizat ce foloseste 3 for-uri si are complexitate O(n^3).

    Am folosit algoritmul de 3 ori, o data tinand cont ca matricea este superior triunghiulara.

## solver_opt.c

    Pentru rezolvarea ecuatiei matriceale am pornit de la programul solver_neopt.c pe care l-am optimizat.

    Folosind laboratorul 5 de pe ocw facut urmatoarele optimizari:

    ->Detectarea constantelor din bucle:
        Prima optimizare consta in faptul ca c[i][j] este o constanta in cadrul buclei k, lucru care nu este evident pentru compilator intrucat aceasta este o referinta in cadrul unui vector, astfel calculam suma intr-o variabila de tip register si ii punem in matrice la finalul buclei k.
        Am folosit register in mai multe variabile pentru a ii spori importanta pentru compilator.
    
    ->Accesul la vectori:
        A doua optimizare a fost transformarea apelarilor statice prin lucrul cu pointeri in felul acesta nu trebuie sa fie calculata de fiecare data adresa din vector, sau trebuie doar sa fie adunat un adumit numar pentru a ajunge la adresa dorita, nu mai trebuie realizate numarul de inmultiri.
        De exemplu in cazul de fata in pointerul orig_pa retinem inceputul randului primei matrici in interiorul buclei i, in bucla j cream 2 noi pointeri, pa pentru a retine locatia din linia din prima matrice ce trebuie inmultita cu coloana celei dea 2 a matrice si pa pentru a retine locatia din coloana celei dea 2 matrice.
        In interiorul buclei k adaugam 1 la pointerul pa pentru a trece la valoarea urmatoare si i * n la pb pentru a trece pe randul urmator pe aceeasi coloana.
        Motivul principal pentru care acest lucru imbunatateste timpul este faptul ca compilatorul tine mai usor cont de pozitia la care ne aflam in vector.
        ->Viteza crescuta insa, va fi obtinuta cu pretul unui cod mult mai dificil de urmarit si de inteles, mai rau, mult mai greu de debug-at.<-

    ->Optimizarea pentru accesul la memorie:
        Pentru fiecare dintre cele trei matrice, a, b si c, fiecare element poate fi accesat in trei moduri diferite, si anume:
            -Constant: accesul nu depinde de indexul buclei interioare
            -Secvential: aceesul la memorie este contiguu (adica in celule succesive de memorie)
            -Nesecvential: accesul la memorie nu este contiguu (celulele de memorie logic succesive, sunt de fapt adresate cu pauze de dimensiune N).

        In cazul folosit in programul cu pricina s-a incercat o schimbare:
        i-k-j:	Secvential	Constant	Secvential.
        Am ales acest mod deoarece nu are portiuni de memorie nesecventiale, in felul acesta folosind memoria intr-un mod mai optim pentru cashe.

# Graficele
    Din graficul din arhiva se poate observa cum cel mai optim program pentru rezolvarea ecuatiei matriceale este blas, urmat de opt si neopt care are un timp de executie de pana la 4 ori mai mare decat opt.

# Fisierele cashe
    In fisierele .cashe se pot face comparatii cu privire la numarul de operatii (refs), numarul de miss-uri, rata de miss si numarul operatiilor de precizie(branches).

        

    



