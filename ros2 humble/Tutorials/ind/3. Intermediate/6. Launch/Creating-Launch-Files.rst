Membuat file peluncuran
======================

**Sasaran:** Membuat file peluncuran untuk menjalankan sistem ROS 2 yang kompleks.

**Tingkat tutorial:** Menengah

**Waktu:** 10 menit

.. isi :: Isi
    :kedalaman: 2
    :lokal:

Prasyarat
-------------

Tutorial ini menggunakan paket :doc:`rqt_graph dan turtlesim <../../Beginner-CLI-Tools/Introducing-Turtlesim/Introducing-Turtlesim>`.

Anda juga perlu menggunakan editor teks pilihan Anda.

Seperti biasa, jangan lupa untuk mencari sumber ROS 2 di :doc:`setiap terminal baru yang Anda buka <../../Beginner-CLI-Tools/Configuring-ROS2-Environment>`.

Latar belakang
----------

Sistem peluncuran di ROS 2 bertanggung jawab untuk membantu pengguna menjelaskan konfigurasi sistem mereka dan kemudian menjalankannya seperti yang dijelaskan.
Konfigurasi sistem mencakup program apa yang akan dijalankan, di mana menjalankannya, argumen apa yang akan diteruskan, dan konvensi khusus ROS yang memudahkan untuk menggunakan kembali komponen di seluruh sistem dengan memberi masing-masing konfigurasi yang berbeda.
Ia juga bertanggung jawab untuk memantau status proses yang diluncurkan, dan melaporkan dan/atau bereaksi terhadap perubahan status proses tersebut.

Luncurkan file yang ditulis dengan Python, XML, atau YAML dapat memulai dan menghentikan node yang berbeda serta memicu dan bertindak pada berbagai peristiwa.
Lihat :doc:`../../../How-To-Guides/Launch-file-different-formats` untuk deskripsi format yang berbeda.
Paket yang menyediakan framework ini adalah ``launch_ros``, yang menggunakan framework ``launch`` non-ROS-spesifik di bawahnya.

`Dokumen desain <https://design.ros2.org/articles/roslaunch.html>`__ merinci tujuan desain sistem peluncuran ROS 2 (tidak semua fungsi tersedia saat ini).

Tugas
-----

1 Pengaturan
^^^^^^^

Buat direktori baru untuk menyimpan file peluncuran Anda:

.. blok kode :: konsol

   peluncuran mkdir

2 Tulis file peluncuran
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Mari kumpulkan file peluncuran ROS 2 menggunakan paket ``turtlesim`` dan file yang dapat dieksekusi.
Seperti disebutkan di atas, ini bisa dalam Python, XML, atau YAML.

.. tab::

   .. grup-tab :: Python

     Salin dan tempel kode lengkap ke file ``launch/turtlesim_mimic_launch.py``:

     .. blok kode :: python

       dari peluncuran impor LaunchDescription
       dari launch_ros.actions impor Node

       def generate_launch_description():
           kembali LaunchDescription([
               Simpul(
                   package='turtlesim',
                   namespace='turtlesim1',
                   dapat dieksekusi='turtlesim_node',
                   nama='sim'
               ),
               Simpul(
                   package='turtlesim',
                   namespace='turtlesim2',
                   dapat dieksekusi='turtlesim_node',
                   nama='sim'
               ),
               Simpul(
                   package='turtlesim',
                   dapat dieksekusi = 'meniru',
                   nama='meniru',
                   pemetaan ulang=[
                       ('/input/pose', '/turtlesim1/turtle1/pose'),
                       ('/keluaran/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
                   ]
               )
           ])

   .. grup-tab :: XML

     Salin dan tempel kode lengkap ke file ``launch/turtlesim_mimic_launch.xml``:

     .. blok kode :: xml

       <peluncuran>
         <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim1"/>
         <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim2"/>
         <node pkg="turtlesim" exec="mimic" name="mimic">
           <remap from="/input/pose" ke="/turtlesim1/turtle1/pose"/>
           <remap from="/output/cmd_vel" to="/turtlesim2/turtle1/cmd_vel"/>
         </simpul>
       </peluncuran>

   .. grup-tab:: YAML

     Salin dan tempel kode lengkap ke file ``launch/turtlesim_mimic_launch.yaml``:

     .. blok kode :: yaml

       meluncurkan:

       - simpul:
           pkg: "kura-kura"
           exec: "turtlesim_node"
           nama: "sim"
           namespace: "turtlesim1"

       - simpul:
           pkg: "kura-kura"
           exec: "turtlesim_node"
           nama: "sim"
           namespace: "turtlesim2"

       - simpul:
           pkg: "kura-kura"
           eksekusi: "meniru"
           nama: "meniru"
           memetakan ulang:
           -
               dari: "/input/pose"
               ke: "/turtlesim1/turtle1/pose"
           -
               dari: "/keluaran/cmd_vel"
               ke: "/turtlesim2/turtle1/cmd_vel"


2.1 Periksa file peluncuran
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Semua file peluncuran di atas meluncurkan sistem tiga node, semuanya dari paket ``turtlesim``.
Tujuan dari sistem ini adalah untuk meluncurkan dua jendela turtlesim, dan satu kura-kura meniru gerakan yang lain.

Saat meluncurkan dua node turtlesim, satu-satunya perbedaan di antara keduanya adalah nilai namespace-nya.
Ruang nama unik memungkinkan sistem untuk memulai dua node tanpa konflik nama node atau nama topik.
Kedua kura-kura dalam sistem ini menerima perintah tentang topik yang sama dan mempublikasikan pose mereka tentang topik yang sama.
Dengan ruang nama yang unik, pesan yang dimaksudkan untuk kura-kura yang berbeda dapat dibedakan.Node terakhir juga dari paket ``turtlesim``, tetapi dapat dieksekusi berbeda: ``mimic``.
Node ini telah menambahkan detail konfigurasi dalam bentuk pemetaan ulang.
Topik ``mimic`` ``/input/pose`` dipetakan ulang ke ``/turtlesim1/turtle1/pose`` dan topik ``/output/cmd_vel`` menjadi ``/turtlesim2/turtle1/cmd_vel` `.
Ini berarti ``mimic`` akan berlangganan ke topik pose ``/turtlesim1/sim`` dan memublikasikannya kembali untuk topik perintah kecepatan ``/turtlesim2/sim`` untuk berlangganan.
Dengan kata lain, ``turtlesim2`` akan meniru gerakan ``turtlesim1``.

.. tab::

   .. grup-tab :: Python

     Pernyataan import ini menarik beberapa modul Python ``launch``.

     .. blok kode :: python

       dari peluncuran impor LaunchDescription
       dari launch_ros.actions impor Node

     Selanjutnya, deskripsi peluncuran itu sendiri dimulai:

     .. blok kode :: python

       def generate_launch_description():
          kembali LaunchDescription([

          ])

     Dua tindakan pertama dalam deskripsi peluncuran meluncurkan dua jendela turtlesim:

     .. blok kode :: python

       Simpul(
           package='turtlesim',
           namespace='turtlesim1',
           dapat dieksekusi='turtlesim_node',
           nama='sim'
       ),
       Simpul(
           package='turtlesim',
           namespace='turtlesim2',
           dapat dieksekusi='turtlesim_node',
           nama='sim'
       ),

     Tindakan terakhir meluncurkan simpul mimik dengan remaps:

     .. blok kode :: python

       Simpul(
           package='turtlesim',
           dapat dieksekusi = 'meniru',
           nama='meniru',
           pemetaan ulang=[
             ('/input/pose', '/turtlesim1/turtle1/pose'),
             ('/keluaran/cmd_vel', '/turtlesim2/turtle1/cmd_vel'),
           ]
       )

   .. grup-tab :: XML

     Dua tindakan pertama meluncurkan dua jendela turtlesim:

     .. blok kode :: xml

       <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim1"/>
       <node pkg="turtlesim" exec="turtlesim_node" name="sim" namespace="turtlesim2"/>

     Tindakan terakhir meluncurkan simpul mimik dengan remaps:

     .. blok kode :: xml

       <node pkg="turtlesim" exec="mimic" name="mimic">
         <remap from="/input/pose" ke="/turtlesim1/turtle1/pose"/>
         <remap from="/output/cmd_vel" to="/turtlesim2/turtle1/cmd_vel"/>
       </simpul>

   .. grup-tab:: YAML

     Dua tindakan pertama meluncurkan dua jendela turtlesim:

     .. blok kode :: yaml

       - simpul:
           pkg: "kura-kura"
           exec: "turtlesim_node"
           nama: "sim"
           namespace: "turtlesim1"

       - simpul:
           pkg: "kura-kura"
           exec: "turtlesim_node"
           nama: "sim"
           namespace: "turtlesim2"


     Tindakan terakhir meluncurkan simpul mimik dengan remaps:

     .. blok kode :: yaml

       - simpul:
           pkg: "kura-kura"
           eksekusi: "meniru"
           nama: "meniru"
           memetakan ulang:
           -
               dari: "/input/pose"
               ke: "/turtlesim1/turtle1/pose"
           -
               dari: "/keluaran/cmd_vel"
               ke: "/turtlesim2/turtle1/cmd_vel"


3 peluncuran ros2
^^^^^^^^^^^^^^^

Untuk menjalankan file peluncuran yang dibuat di atas, masuk ke direktori yang Anda buat sebelumnya dan jalankan perintah berikut:

.. tab::

   .. grup-tab :: Python

     .. blok kode :: konsol

       peluncuran cd
       ros2 meluncurkan turtlesim_mimic_launch.py

   .. grup-tab :: XML

     .. blok kode :: konsol

       peluncuran cd
       ros2 meluncurkan turtlesim_mimic_launch.xml

   .. grup-tab:: YAML

     .. blok kode :: konsol

       peluncuran cd
       ros2 meluncurkan turtlesim_mimic_launch.yaml

.. catatan::

   Dimungkinkan untuk meluncurkan file peluncuran secara langsung (seperti yang kami lakukan di atas), atau disediakan oleh sebuah paket.
   Ketika disediakan oleh sebuah paket, sintaksnya adalah:

   .. blok kode :: konsol

       ros2 luncurkan <nama_paket> <nama_file_peluncuran>

   Anda belajar tentang membuat paket di :doc:`../../Beginner-Client-Libraries/Creating-Your-First-ROS2-Package`.

.. catatan::

   Untuk paket dengan file peluncuran, sebaiknya tambahkan dependensi ``exec_depend`` pada paket ``ros2launch`` dalam paket ``package.xml``:

   .. blok kode :: xml

     <exec_depend>ros2launch</exec_depend>

   Ini membantu memastikan bahwa perintah ``ros2 launch`` tersedia setelah membangun paket Anda.
   Ini juga memastikan bahwa semua :doc:`launch file format <../../../How-To-Guides/Launch-file-different-formats>` dikenali.

Dua jendela turtlesim akan terbuka, dan Anda akan melihat pesan ``[INFO]`` berikut yang memberi tahu node mana yang telah dimulai oleh file peluncuran Anda:

.. blok kode :: konsol

   [INFO] [peluncuran]: Verbositas logging default diatur ke INFO
   [INFO] [turtlesim_node-1]: proses dimulai dengan pid [11714]
   [INFO] [turtlesim_node-2]: proses dimulai dengan pid [11715]
   [INFO] [mimic-3]: proses dimulai dengan pid [11716]

Untuk melihat sistem beraksi, buka terminal baru dan jalankan perintah ``ros2 topic pub`` pada topik ``/turtlesim1/turtle1/cmd_vel`` untuk menggerakkan turtle pertama:

.. blok kode :: konsol

   ros2 topik pub -r 1 /turtlesim1/turtle1/cmd_vel geometri_msgs/msg/Putar "{linear: {x: 2.0, y: 0.0, z: 0.0}, sudut: {x: 0.0, y: 0.0, z: -1.8}}"

Anda akan melihat kedua kura-kura mengikuti jalur yang sama.

.. gambar:: gambar/mimic.png

4 Introspeksi sistem dengan rqt_graph
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Saat sistem masih berjalan, buka terminal baru dan jalankan ``rqt_graph`` untuk mendapatkan gambaran yang lebih baik tentang hubungan antara node di file peluncuran Anda.

Jalankan perintah:

.. blok kode :: konsol

   rqt_graph

.. gambar:: images/mimic_graph.png

Node tersembunyi (perintah ``ros2 topic pub`` yang Anda jalankan) menerbitkan data ke topik ``/turtlesim1/turtle1/cmd_vel`` di sebelah kiri, yang menjadi langganan node ``/turtlesim1/sim`` .
Sisa grafik menunjukkan apa yang dijelaskan sebelumnya: ``mimic`` berlangganan topik pose ``/turtlesim1/sim``, dan menerbitkan topik perintah kecepatan ``/turtlesim2/sim``.

Ringkasan
-------

Luncurkan file menyederhanakan menjalankan sistem yang kompleks dengan banyak node dan detail konfigurasi khusus.
Anda dapat membuat file peluncuran menggunakan Python, XML, atau YAML, dan menjalankannya menggunakan perintah ``ros2 launch``.