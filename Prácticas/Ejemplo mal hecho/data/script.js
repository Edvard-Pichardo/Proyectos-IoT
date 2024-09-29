// script.js
document.getElementById('cambiarFondo').addEventListener('click', function() {
    // Generar un color aleatorio en formato hexadecimal
    var colorHexadecimal = '#' + Math.floor(Math.random() * 16777215).toString(16);

    // Aplicar el nuevo color de fondo a body
    document.body.style.backgroundColor = colorHexadecimal;
});
