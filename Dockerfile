# Usar la imagen oficial de Nginx como base
FROM nginx:alpine

# Elimina la configuración predeterminada de Nginx
RUN rm -rf /usr/share/nginx/html/*

# Copiar los archivos de tu sitio web a la imagen
COPY . /usr/share/nginx/html

# Exponer el puerto 80 para el servidor web
EXPOSE 80

# Comando para ejecutar Nginx en modo foreground
CMD ["nginx", "-g", "daemon off;"]
