cpp -dD -P -fpreprocessed | tr -d '\r\n\t ' | md5sum | cut -c-6 || echo "000000"
