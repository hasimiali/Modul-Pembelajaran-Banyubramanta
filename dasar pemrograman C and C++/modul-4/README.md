## Daftar Isi
- [Pointer](#pointer)
   + [Alamat Memori](#alamat-memori)
   + [Pengenalan Pointer](#pengenalan-pointer)
   + [Double Pointer](#double-pointer)
   + [Pointer dan Array](#pointer-dan-array)
   + [Pointer dan Fungsi](#pointer-dan-fungsi)
- [Struct](#struct)
   + [Pengenalan Struct](#pengenalan-struct)
   + [Deklarasi Struct](#deklarasi-struct)
   + [Variabel Struct](#variabel-struct)
   + [Akses Member Struct](#akses-member-struct)
   + [Array of Struct](#array-of-struct)
- [Soal Latihan](#soal-latihan)

***

# Pointer

## Alamat Memori

### Operator Address-Of (&)

Setiap variabel, fungsi, struct, ataupun objek lain yang dibuat dalam program mempunyai lokasi masing-masing pada memori. Alokasi setiap variabel disimpan dalam alamat memori tertentu. 

Misalnya:\
Terdapat variabel bernama `var`. Untuk mengetahui alamat memori dari variabel, digunakan **operator address-of (&)** di depan nama variabelnya.

```C
int var = 5;
printf("%d\n", var);
printf("%p\n", &var);
```

**Output**:
```
5
0x7fffdeb3ed84
```

Output bisa berbeda-beda di tiap eksekusi.\
**0x7fffdeb3ed84** merupakan alamat memori dari variabel `var`.

***

## Pengenalan Pointer 

Pointer adalah variabel spesial yang menampung alamat memori, bukan nilai seperti variabel biasa.

### Deklarasi Variabel Pointer 

Deklarasi variabel pointer menggunakan operator `*` di antara tipe data dan nama variabelnya.

```C
int *ptr;
```
atau
```C
int* ptr;
```
Kedua cara deklarasi di atas merupakan sintaks yang valid.

### Inisialisasi Variabel Pointer

Variabel `ptr` di atas adalah variabel pointer yang bertipe int. Variabel pointer menampung alamat memori. Inisialisasi variabel pointer harus berupa alamat memori, bisa dari variabel lain atau alokasi secara dinamis.

```C
int var = 55;
int *ptr = &var; // Inisialisasi menggunakan alamat dari var
```

Inisialisasi yang tidak sesuai akan menghasilkan error atau _undefined behaviour_.

```C
// ERROR
int *ptr  = 5;
// UNDEFINED BEHAVIOUR
int *ptr2 = 0x7fffdeb3ed84;
```

### Assignment Variabel Pointer
Cara melakukan assignment pada variabel pointer tidak sama dengan inisialisasinya.

```C
int var, *ptr;
var = 55;
ptr = &var; // Assignment pada variabel pointer menggunakan alamat dari var
```

Assignment tidak perlu menggunakan simbol * di depan nama variabelnya. Berbeda pada saat deklarasi yang mana kita perlu memberitahu compiler bahwa variabel tersebut adalah variabel pointer.

### Operator Dereference (*)

Operator dereference menggunakan simbol yang sama dengan simbol operator perkalian, yakni * (simbol asterisk). Namun, fungsinya sangat berbeda. Operator dereference digunakan untuk mengakses nilai yang ditunjuk (*pointed*) dari sebuah variabel pointer.

Untuk mengakses nilai dari sebuah variabel pointer, digunakan operator dereference di depan nama variabel pointer.

```C
int var  = 55;
int *ptr = &var;

printf("%d\n", *ptr);
*ptr = 20;

printf("%d\n", *ptr);
printf("%d\n", var);
```

**Output**
```C
55
20
20
```

Apa output dari program di bawah ini?
```C
#include <stdio.h>

int main(void)
{
    int x, y, z;
    int *ptr1, *ptr2;
    x = 5;
    y = 6;

    ptr1 = &x;
    ptr2 = &y;

    z = *ptr1 + *ptr2;
    printf("%d\n", z);
    
    return 0;
}
```

## Double Pointer

Variabel pointer juga dapat menunjuk variabel pointer lainnya. Hal ini disebut dengan **_double pointer_** (*pointer to pointer*). Untuk mendeklarasikan variabel _double pointer_, digunakan dua simbol *. Kegunaan paling umum dari variabel _double pointer_ adalah untuk membuat array dua dimensi secara dinamis.

```c
int **dbPtr;
```
Variabel `dbPtr` di atas menyimpan alamat memori dari variabel pointer lainnya.

```c
#include <stdio.h>

int main(void)
{
    int var = 23;
    int *ptr = &var;
    int **dbPtr = &ptr;

    printf("%d\n", **dbPtr);
    
    return 0;
}
```

## Pointer dan Array

Kita sudah mengetahui bahwa array adalah kumpulan data yang disusun secara sekuensial. Karena disusun secara sekuensial, alamat-alamat memori tiap elemen array juga tersusun secara berurutan.

![memory](https://github.com/AlproITS/DasarPemrograman/blob/master/img/memory.PNG)

Bagaimana jika kita ingin mengetahui alamat memori dari array?

```c
#include <stdio.h>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int i;
    for (i = 0; i < 5; ++i) {
        printf("&arr[%d] => %p\n", i, &arr[i]);
    }
    printf("Address of arr => %p\n", arr);
    return 0;
}
```

**Output**
```
&arr[0] => 0x7fffe85f0520
&arr[1] => 0x7fffe85f0524
&arr[2] => 0x7fffe85f0528
&arr[3] => 0x7fffe85f052c
&arr[4] => 0x7fffe85f0530
Address of arr => 0x7fffe85f0520
```

Dapat diperhatikan bahwa alamat dari `&arr[0]` sama dengan alamat dari `arr`. Dari hal ini dapat diketahui bahwa nama array menunjuk ke elemen pertama dari array tersebut. Karena `&arr[0]` = `arr`, maka dapat disimpulkan bahwa `arr[0]` = `*arr`, atau nilai dari elemen pertama dapat diakses dengan `*arr` atau `*(arr + 0)`.

arr[0] = *(arr + 0)\
arr[1] = *(arr + 1)\
arr[2] = *(arr + 2)\
.\
.\
dst

**Kesimpulan**: Nama array merujuk pada alamat memori dari elemen pertama pada array.
Berbekal dari hal tersebut, maka kita dapat melakukan hal demikian.

```c
#include <stdio.h>

int main()
{
    int arr[5] = {1, 2, 3, 4, 5}, i;
    int *ptr = arr;

    for (i = 0; i < 5; ++i) {
        printf("%d ", *(ptr+i));
    }
    return 0;
}
```

**Output**
```
1 2 3 4 5
```

## Pointer dan Fungsi

Sebelumnya kita sudah mengetahui bahwa fungsi dapat menerima parameter sebagai input. Penggunaan-penggunaan parameter fungsi selama ini sebenarnya menggunakan konsep **_pass by value_**. Selain menggunakan cara itu, terdapat cara lain untuk _passing_ argumen pada fungsi.

<img src="https://blog.penjee.com/wp-content/uploads/2015/02/pass-by-reference-vs-pass-by-value-animation.gif">

### Pass by Value

**_Pass by Value_** berarti saat kita memasukkan (_passing_) argumen pada fungsi, nilai dari argumen tersebut akan disalin ke variabel yang berada pada parameter fungsi. Karena hanya nilainya saja yang diterima oleh fungsi, perubahan yang terjadi pada variabel parameter fungsi tidak akan berpengaruh terhadap variabel asalnya.

Contoh:
```c
#include <stdio.h>

void change(int a, int b)
{
    a = a + 5;
    b = b + 5;
}

int main()
{
    int x = 10, y = 6;
    change(x, y);
    printf("%d %d\n", x, y);

    return 0;
}
```

**Nilai pada variabel `x` dan `y` tidak berubah karena metode _passing_ yang digunakan adalah _Pass by Value_**.

### Pass by Address/Reference

Berbeda dengan sebelumnya, sesuai namanya, metode **Pass by Address** berarti argumen yang dimasukkan (_passing_) ke parameter fungsi adalah alamat memori variabel. **Segala perubahan yang terjadi pada variabel tersebut, juga mempengaruhi langsung ke variabel asalnya**. Hal ini terjadi karena argumennya adalah langsung berupa alamat memorinya.

```c
#include <stdio.h>

void change(int *a, int *b)
{
    *a = *a + 5;
    *b = *b + 5;
}

int main()
{
    int x = 10, y = 6;
    change(&x, &y);
    printf("%d %d\n", x, y);

    return 0;
}
```

Karena parameternya menerima alamat memori, maka variabel parameternya harus berupa pointer.

Passing array sebagai parameter fungsi juga dapat dilakukan dengan pointer. Segala perubahan pada array akan berpengaruh pada array asalnya.

```c
#include <stdio.h>

void printArr(int *arr)
{
    // ...
    // ...
}

int main()
{
    int num[5] = {1, 2, 3, 4, 5}, i;
    printArr(num);
    // ...
    // ...
    return 0;
}
```

# Struct

## Pengenalan Struct

Dalam bahasa C, struct adalah salah satu tipe data turunan atau bisa disebut juga **user defined data type** yang dapat mengelompokkan beberapa variabel di bawah satu nama. Tidak seperti array yang hanya dapat menyimpan elemen dengan tipe data sama, **struct dapat mengelompokkan elemen dengan tipe data yang berbeda-beda**.

Contoh:

<img src="https://github.com/AlproITS/DasarPemrograman/blob/master/img/struct.PNG" width="200px">

Perhatikan gambar di atas. Mahasiswa merupakan suatu entitas yang di dalamnya terdapat atribut-atribut berupa:
   + Nama
   + NRP
   + Umur
   + IPK
   + Semester
   + Status

Atribut-atribut inilah yang nantinya berperan sebagai member dari struct `Mahasiswa`.

### Deklarasi Struct

Seperti variabel, struct harus dideklarasikan terlebih dahulu sebelum bisa digunakan. Pendeklarasian struct menggunakan sintaks sebagai berikut.

```c
struct <nama_struct> {
    <tipe_data_member> <nama_member>;
    <tipe_data_member> <nama_member>;
    <tipe_data_member> <nama_member>;
    .
    .
    .
};
```

Berikut adalah contoh deklarasi struct berdasarkan kasus Mahasiswa di atas.

```c
struct Mahasiswa {
    char nama[100];
    char nrp[20];
    int umur;
    double ipk;
    int semester;
    int status;
};
```

### Variabel Struct

Setelah dideklarasikan, sebuah struct akan menjadi tipe data baru. Maka dalam kasus ini, struct `Mahasiswa` di sini menjadi tipe data baru dengan member-member berupa `nama`, `nrp`, `umur`, `ipk`, `semester`, dan `status`. Untuk membuat variabel dengan tipe data struct, dilakukan dengan sintaks berikut.

```c
struct <nama_struct> <nama_variabel>;
```

Contoh:
```c
struct Mahasiswa mhs1;
struct Mahasiswa mhs2;
```

Contoh di atas menunjukkan terdapat dua variabel `mhs1` dan `mhs2` bertipe struct `Mahasiswa`.

### Akses Member Struct

Lalu bagaimana cara untuk mengakses member dari variabel struct yang telah dibuat? Untuk mengakses member-member dari struct, digunakan operator dot (.) setelah nama variabelnya.

```c
<nama_variabel>.<member_struct>
```

Contoh:
```c
mhs1.umur = 19;
mhs1.semester = 3;

mhs2.umur = 20;
mhs2.semester = 5;
```

Contoh program untuk mendemonstrasikan Struct:
```c
#include <stdio.h>
#include <string.h>

struct Mahasiswa {
    char nama[100];
    char nrp[20];
    int umur;
    double ipk;
    int semester;
    int status;
};

int main(void)
{
    struct Mahasiswa mhs1;

    strcpy(mhs1.nama, "Ahmad");
    strcpy(mhs1.nrp, "05111940000012");
    mhs1.umur = 18;
    mhs1.ipk = 3.94;
    mhs1.semester = 3;
    mhs1.status = 1;

    printf("Nama\t: %s\n", mhs1.nama);
    printf("NRP\t: %s\n", mhs1.nrp);
    printf("Umur\t: %d\n", mhs1.umur);
    printf("IPK\t: %.2lf\n", mhs1.ipk);
    printf("Sem\t: %d\n", mhs1.semester);
    printf("Status\t: %s\n", (mhs1.status == 1 ? "Aktif" : "Tidak Aktif"));
    
    return 0;
}
```

### Array of Struct

Kita juga dapat membuat array dengan tipe data struct. Caranya sama persis dengan deklarasi array pada umumnya.

```c
#include <stdio.h>
struct Point {
    int x, y;
};

int main()
{
    struct Point arr[3];
    arr[0].x = 2, arr[0].y = 3;
    arr[1].x = 5, arr[1].y = 3;
    arr[2].x = 2, arr[2].y = 8;

    printf("%d %d\n", arr[0].x, arr[0].y);
    printf("%d %d\n", arr[1].x, arr[1].y);
    printf("%d %d\n", arr[2].x, arr[2].y);
    
    return 0;
}
```

# Soal Latihan

## Soal 1

Implementasikan fungsi bernama tambah berisi 3 parameter, di mana parameter pertama merupakan bilangan 1, parameter kedua merupakan bilangan 2, dan parameter terakhir adalah variabel tempat hasil output.

Contoh pemanggilan:
```c
int a = 1;
int b = 2;
int c;
tambah(a, b, &c);
printf(“%d”, c);
```

Output-nya:
```
3
```

## Soal 2
Buatlah struct untuk menyimpan data nilai UN mahasiswa yang berisi nama, nilai Matematika, nilai IPA, nilai Bahasa Indonesia, dan nilai Bahasa Inggris. Setelah itu buat program yang dapat memasukkan list data nilai UN lalu menampilkan data sesuai nama.

Keterangan: urutan pemasukan nilai adalah Matematika, IPA, Bahasa Indonesia, Bahasa Inggris. Berikut merupakan contoh input dan output. 4 kelompok data di awal merupakan jumlah data nilai UN yang akan dimasukkan. Angka 3 di akhir merupakan jumlah nama yang akan dicari.

Sample Input
```
4
Hope
100
90
20
90
Ricky
80
70
80
90
Maden
100
100
100
100
Tenten
90
80
99
100
3
Maden
Dennis
Tenten
```

Sample Output
```
Nilai Maden 
Matematika : 100
IPA : 100
Bahasa Indonesia : 100
Bahasa Inggris : 100
Nilai Dennis tidak ditemukan
Nilai Tenten
Matematika : 90
IPA : 80
Bahasa Indonesia : 99
Bahasa Inggris : 100
```

## Soal 3
Buatlah fungsi bernama **reverse()** untuk me-reverse array of integer menggunakan pointer. Fungsinya dapat digunakan seperti berikut.

```c
int arr[5]
.
.
//input

reverse(arr, 5);
.
.
//print isi arr

```

Sample Input:
```
5
8 4 2 3 1
```

Sample Output:
```
1 3 2 4 8
```