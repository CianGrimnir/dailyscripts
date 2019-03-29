#!/bin/bash

cd /tmp/LOGS
(echo -e "Files getting deleted\n";
find . -iname "file_new_[2|f]*" -mmin +360) > temp_list
find . -iname "file_new_[2|f]*" -mmin +360 -delete
find . \( -iname "file_new_log*" -o -iname "log_bin_file*" \)  -a -not -name "*.zip" -mmin +360 -exec zip -m /home/USER/FILEDBKP/'{}'.zip '{}' \;
