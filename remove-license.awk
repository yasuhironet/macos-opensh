
BEGIN {
comment_start=0;
comment_end=0;
}

/\/\*/ {
  comment_start+=1;
}

// {
  if (comment_start != 0 && comment_end != 0) {
    print $0;
  }
}

/\*\// {
  comment_end+=1;
}

