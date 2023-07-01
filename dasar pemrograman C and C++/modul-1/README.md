## Daftar Isi

- [Control Flow](#control-flow)
- [Percabangan](#percabangan)
    + [If](#percabangan-if)
    + [If-Else](#percabangan-if-else)
    + [If-Else if](#percabangan-if-elseif)
    + [Switch-Case](#percabangan-switch-case)
    + [Operator Kondisional ( ? : )](#operator-kondisional--)
- [Soal Latihan](#soal-latihan)

# Control Flow
Control Flow adalah cara kita mengatur jalan penyataan, instruksi, dan pemanggilan fungsi  suatu program. Tanpa control flow, program kita hanya bergerak dari atas ke bawah saja (**sequential**). Control flow bahasa C ada 2, yaitu percabangan (**selection**) dan perulangan (**repetition**). Di Modul ini, kita akan memfokuskan pembahasan di percabangan terlebih dahulu.

# Percabangan
Percabangan memungkinkan kita untuk menentukan kode manakah yang akan kita eksekusi berdasarkan suatu kondisi. Percabangan di bahasa C ada 4, yaitu `if`, `if-else`, `if-else if`, dan `switch`.

## Percabangan If

Sintaks yang digunakan dalam percabangan menggunakan `if` adalah sebagai berikut.

```c
if (<Ekspresi/Kondisi>) {

    // Kode yang akan dieksekusi jika kondisi tersebut benar

}
```

Cara kerja percabangan `if` yaitu memeriksa dan mengevaluasi suatu kondisi untuk menentukan apakah instruksi selanjutnya dalam _bracket_ akan dijalankan atau tidak oleh program.
- Jika kondisi tersebut bernilai **TRUE (1)**, kode yang di dalam bracket akan **dieksekusi**. 
- Sebaliknya jika kondisi tersebut bernilai **FALSE (0)**, kode yang di dalam bracket **tidak akan dieksekusi**.

Contoh

Sebagai contoh, di dashboard mobil terdapat indikator bahan bakar yang akan **menyala jika bahan bakar yang tersisa kurang dari level tertentu (misal kurang dari 10 liter)** dengan kondisi “Apakah bahan bakar kurang dari 10 liter?”.

Pada kasus ini terdapat kondisi
- **Jika bahan bakar kurang dari 10 liter** maka nyalakan lampu indikator.

```c
#include <stdio.h>
int main()
{
    int gasoline = 0;
    gasoline = 3;
    if (gasoline < 10) //jika bahan bakar kurang dari 10 liter
    {
        // Apa yang perlu dilakukan ketika kondisi terpenuhi?
        printf("Lampu Indikator menyala!\n");
    }
}
```

Output

```
Lampu Indikator menyala!
```

## Percabangan If-Else

Sintaks yang digunakan dalam percabangan menggunakan `if-else` adalah sebagai berikut.

```c
if (<Ekspresi/Kondisi>) {

    // Kode yang akan dieksekusi jika kondisi tersebut benar

} else {

    // Kode yang akan dieksekusi jika kondisi tersebut salah

}
```

Cara kerja percabangan `if-else` yaitu memeriksa kondisi dalam `if`.
- Jika kondisi tersebut bernilai **TRUE (1)**, Program akan **menjalankan kode di dalam bracket `if`**.
- Sebaliknya jika kondisi tersebut bernilai **FALSE (0)**, kode di bawah **`else`** lah **yang akan dijalankan**.

Sebagai contoh, kita ingin mencari tahu apakah seseorang absen dari kelas atau tidak. **Apabila ia tidak hadir, maka absensinya akan dicoret (bernilai X)**, dan **apabila hadir, maka absensinya akan di centang (bernilai V)**.

Sehingga dari kasus tersebut, didapat dua alternatif kondisi.
- **Apabila ia hadir, maka muncul V**
- **Apabila ia tidak hadir, maka muncul X**

```c
#include <stdio.h>
#define DATANG 1

int main()
{
    int hadir = DATANG;
    if (hadir) // Jika orang tersebut hadir
    {
        printf("V\n");
    } else {
        printf("X\n");
    }
}
```

Output

```
V

```

## Percabangan If-Else if

Sintaks yang digunakan dalam percabangan menggunakan `if-else if` adalah sebagai berikut.

```c
if (<Ekspresi/Kondisi>) {

    // Kode yang akan dieksekusi jika kondisi tersebut benar

}else if (<Ekspresi/Kondisi>) {

    // Kode yang akan dieksekusi jika kondisi tersebut salah

}
// Boleh menambahkan else{} apabila perlu
```

Cara kerja percabangan `if-else` yaitu memeriksa kondisi dalam `if`.
- Jika kondisi tersebut bernilai **TRUE (1)**, Program akan **menjalankan kode di dalam bracket `if`**.
- Apabila kondisi pertama tidak memenuhi, maka ia akan memerika kondisi didalam `else-if`, apabila bernilai **TRUE (1)**, maka ia akan **menjalankan perintah dalam bracket tersebut**, apabila tidak maka ia akan menjalankan sequence selanjutnya.
- Apabila kita menyediakan statement else diakhir, maka ketika **seluruh kondisi** `if` dan `else-if` tidak memenuhi atau **FALSE (0)**, maka secara otomatis ia akan **menjalankan perintah di dalam `else`** tersebut.

## Percabangan Switch-Case

Selain penggunaan statement `if` untuk memilih diantara banyak alternatif, terdapat pula statement `switch` yang memiliki fungsi yang sama, untuk memilih diantara banyak alternatif berdasarkan sebuah kondisi. Kondisi pada statemen `switch` berisi ekspresi yang dapat menggunakan sebuah variable tunggal bertipe int atau char yang akan diperiksa nilainya di setiap blok case.

Sintaks untuk Switch-Case:

```c
switch(ekspresi) {

    case ekspresi-konstan:
        statement;
        break;

    case ekspresi-konstan:
        statement;
        break;
  
    /* Anda bisa memiliki jumlah case sebanyak mungkin */

    /* Anda harus mengakhiri blok kode Switch-Case dengan "default",
       yaitu bagian kode yang akan dieksekusi jika tidak ada case yang memenuhi */

    default: 
        statement;
}
```

Setiap blok, case harus ditambahkan statement **``break``**, karena apabila tidak maka ia akan tetap menjalankan blok case di bawahnya hingga bertemu `break` lain atau pada akhir blok switch.

Contoh

```c
#include <stdio.h>

int main()
{
    char platNomor;
    printf("Masukkan huruf awal plat nomor anda: ");
    scanf("%c", &platNomor);

    switch(platNomor)
    {
        case 'L':
            printf("Surabaya");
            break;

        case 'B':
            printf("Jakarta");
            break;

        case 'D':
            printf("Bandung");
            break;

        case 'N':
            printf("Malang/Lumajang");
            break;

        default:
            printf("Karakter plat nomor tidak diketahui");
    } 
    return 0;
}
```

Dalam contoh di atas, **ekspresi** yang digunakan adalah **PlatNomor**, di mana **case-case** nya adalah, huruf plat nomor tersebut, L, B, D, N, dan sebagainya.

## Operator Kondisional (` ? : `)

Operator kondisional mempunyai bentuk sintaks sebagai berikut:

```
(ekspresi/kondisi) ? (ekspresi jika TRUE) : (ekspresi jika FALSE);
```

Operator kondisional adalah satu-satunya operator ternary dalam bahasa C. Operator kondisional bertingkah seperti layaknya percabangan `if - else`. Ekspresi/kondisi yang akan dievaluasi diletakkan sebelum tanda tanya (`?`). Apabila menghasilkan **TRUE**, maka program akan mengeksekusi bagian di **kiri** tanda titik dua. Jika **FALSE**, akan mengeksekusi bagian di **kanan** tanda titik dua.

Contoh:

```c
#include <stdio.h>

int main()
{
    int mark;
    
    scanf("%d", &mark);
    printf(mark >= 75 ? "Lulus\n" : "Tidak Lulus\n");
    return 0;
}
```

Program di atas ekuivalen dengan:

```c
#include <stdio.h>

int main()
{
    int mark;
    
    scanf("%d", &mark);
    if (mark >= 75) {
        printf("Lulus\n");
    } else {
        printf("Tidak Lulus\n");
    }
    return 0;
}
```

# Soal Latihan

## Soal 1

Buatlah program yang dapat menentukan apakah suatu input bilangan dari 0 sampai 999 merupakan bilangan Armstrong.

**Sample Input 1**
```
153
```
**Sample Output 1**
```
Merupakan Bilangan Armstrong
```

**Sample Input 2**
```
25
```
**Sample Output 2**
```
Bukan Merupakan Bilangan Armstrong
```

Catatan:
153 merupakan bilangan armstrong karena 153 = 1^3 + 5^3 + 3^3

## Soal 2

Buatlah program yang hanya menerima inputan 0 sampai 999 dan mengeluarkan hasil berupa kalimat terbilang dari angka yang dimasukan.

**Sample Input 1**
```
1
```
**Sample Output 1**
```
Satu
```

**Sample Input 2**
```
11
```
**Sample Output 2**
```
Sebelas
```

**Sample Input 3**
```
979
```
**Sample Output 3**
```
Sembilan ratus tujuh puluh sembilan
```

## Soal 3

A, B, C, D, E, F, G merupakan input sinyal untuk sebuah digit dari 0 sampai 9 seperti berikut.

![seven-segment](https://www.realdigital.org/img/83efb712b75cf12d4a31f4ed93b7b16c.svg)

Buatlah program yang menerima input I1, I2, I3, I4 dan keluarkan output berupa nilai dari ketujuh input sinyal (1 menyala, 0 mati).
(Input I1, I2, I3, I4 bertindak sebagai notasi biner. Contoh 1 0 0 0 bernilai 8)

**Sample Input 1**
```
0 0 0 0
```
**Sample Output 1**
```
1 1 1 1 1 1 0
```

**Sample Input 2**
```
1 0 1 1
```
**Sample Output 2**
```
0 0 0 0 0 0 0
```