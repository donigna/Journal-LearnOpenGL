## CATATAN OPENGL HELLO TRIANGLE

///
**Vertex Input**
OpenGL merupakan 3D Graphic Library jadi koordinat di OpenGL terdiri dari x,y,z. 
OpenGL melakukan proccess koordinasi yang spesifik diantara -1.0 dan 1.0 di setiap axisnya. Setiap koordinat seperti ini dipanggil dengan normalized device coordinates. Hanya koordinat itu yang bisa ditampakkan di layar.

contoh bentuk vertices : 
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
}

Setelah menentukan vertex data diatas maka kita akan mengirimkannya ke *graphic pipelines:* **vertex shader** 
Dengan cara membuat memory di GPU dimana kita menyimpan vertex data, kemudian atur OpenGL agar mengirimkan memory tersebut ke graphics card.

Kita mengatur itu melalui **VBO(vertex buffer unity)** yang bisa menyimpan banyak sekali vetices di dalam memori GPU.

**buffer** adalah memori sementara yang digunakan untuk menampung data yang sedang diproses

**GL_STATIC_DRAW** untuk gambar yang statis/tidak berubah - ubah
**GL_DYNAMIC_DRAW** untuk gambar yang beberapa kali berubah
**GL_STREAM_DRAW** untuk gambar selalu berubah setiap frame, seperti particle
///

///
**Vertex Shader**
Bahasa yang digunakan oleh OpenGL untuk shader adalah GLSL(OpenGL Shading Language).

contoh basic vertex : 
#version 330 core <-- ini versi core open glnya

layout (location = 0) in vec3 position; <-- location merupakan lokasi penyimpanan buffer di memory

**GLuint** biasa digunakan sebagai id karena nilai uint-nya yang selalu positif dan lebih besar daripada int biasako
///

///
**Fragment Shader**
Fragment shader adalah proses kalkulasi warna output dari pixels. 

Warna graphic komputer direpresentasikan dengan array isi 4 (RGBA). di GLSL untuk menampilkan warna maka kita harus mengisi data array diantara 0.0 - 1.0. 

Kita bisa menghasilkan setidaknya 16 juta warna dari ini

contoh kode fragment : 
#version 330 core

out vec4 color;

void main() {
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
///


