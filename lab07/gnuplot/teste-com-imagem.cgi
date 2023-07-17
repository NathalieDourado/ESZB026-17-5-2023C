#!/bin/bash

ARQUIVODADOS=/home/pi/sist_embarcados_git/lab07/gnuplot/dados.txt
echo "Content-type: text/html"
echo ""
echo '<HTML><HEAD><meta charset="UTF-8">'
echo '<TITLE>Pagina CGI gerando figura</TITLE></HEAD>'
echo '<BODY style="background-color:#FFFFE0"><H1>Página teste CGI e figuras.</H1>'
echo 'Estou no diretório '
pwd
echo ', logado como o usuário '
whoami
echo '.<br>'
echo '<h2>DADOS:</h2>'
echo '<pre>'
cat $ARQUIVODADOS
echo '</pre>'
echo '<br>'
echo '<br>'
echo '<h2>IMAGENS:</h2>'
echo 'Referenciando a imagem como "/cgi-bin/imagem.cgi":<br>'
echo '<img src="/cgi-bin/imagem.cgi">'
echo '<br>'
echo 'Referenciando a imagem como "imagem.cgi":<br>'
echo '<img src="imagem.cgi">'
echo '<br>'
echo '</HTML>'

