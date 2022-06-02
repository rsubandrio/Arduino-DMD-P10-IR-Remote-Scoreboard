# Arduino DMD P10 IR Remote Scoreboard

Hai, ini adalah repository untuk project menggunakan arduino pro mini. Sketch pada project ini dibuat dengan menggunakan **Visual Studio Code** dan ekstensi **Plaformio**.

## Ringkasan Project
Project ini dimaksudkan untuk
> * Menampilkan score olahraga pada dot matrix display P10.
> * Juga menampilkan jam
> * Score tetap tersimpan jika terjadi mati lampu

## Konfigurasi
Project ini dibuat secara khusus untuk digunakan dengan bahan-bahan sebagai berikut:
> * Arduino Pro Mini
> * Panel P10 hub-12
> * RTC DS3231
> * IR Modul berprotokol NEC

Idealnya bisa juga digunakan untuk board lain yang menggunakan platform serupa dengan beberapa perubahan.

Project ini karena dibuat dengan VS Code maka untuk mereplikanya harus dengan vscode dan ekstensi platformio, selain itu anda juga mungkin harus mendownload dan menginstall pustaka (_library_) seperti yang dalam #include di file _main.cpp_

Project ini seharusnya juga dapat direplika pada **Arduino IDE** selama anda tahu caranya.

## Library
> * [IRsmallDecoder](https://github.com/LuisMiCa/IRsmallDecoder)
> * [DMD2](https://github.com/freetronics/DMD2)
> * [RTC](https://github.com/cvmanjoo/RTC)
> * [EEWL](https://github.com/fabriziop/EEWL)

## Lisensi
Project ini boleh digunakan oleh siapa saja, dan semua pustaka (library) dan potongan code yang dipakai dalam project ini merupakan milik dari pemegang hak ciptanya, yang saya hargai dan seharusnya anda juga.

## Troubles and Issues
Setiap manusia wajib mempertanggungjawabkan setiap perbuatannya sendiri. Segala kerusakan terhadap board ataupun properti lain anda akibat langsung maupun tidak langsung dari menggunakan sketch dari saya ini, bukan tanggung jawab saya.

Silahkan gunakan fitur **issues** jika saya memiliki sumber daya akan saya coba jawab.
