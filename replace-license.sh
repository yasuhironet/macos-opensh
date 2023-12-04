

files=`ls */*.[ch]`

for file in $files; do
  cp $file $file.bak
  cat $file.bak | awk -f remove-license.awk > $file
  sed -e '1rLICENSE-GNU' -i .sbk $file
  rm -f $file.bak
done

