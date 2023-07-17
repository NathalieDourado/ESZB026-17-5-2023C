#!/bin/bash
echo "Content-type: text/html"
echo ""
echo '<HTML><HEAD><meta charset="UTF-8">'
echo '<TITLE>Pagina com CGI</TITLE></HEAD>'
echo '<BODY><H1>Página teste com CGI.</H1>'
echo '<PARA>'
hostname
echo ' está ligado. Uptime: '
uptime
echo '</PARA></HTML>'

