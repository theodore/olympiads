var
  r,n:string;
  now,rt:array[1..10000] of integer;
  nt,i,j,tl,e,t,p:integer;
  po,len:longint;
  s:array[1..43] of string;
procedure times;
var
  t,i,j:integer;
  ot:array[1..10000] of integer;
begin
  fillchar(ot,sizeof(ot),0);
  for i:=1 to tl do
  begin
    t:=0;
    for j:=1 to len do
    begin
      t:=t+now[j]*rt[i]+ot[i+j-1];
      ot[i+j-1]:=t mod 10;
      t:=t div 10;
    end;  
    ot[i+j]:=t;
  end;
  len:=len+tl;
  while (ot[len]=0) and (len>1) do dec(len);
  now:=ot;
end;

begin
  j:=1;
  fillchar(s,sizeof(s),0);
  while not eof do
  begin
    p:=0;
    fillchar(now,sizeof(now),0);
    fillchar(rt,sizeof(rt),0);
    readln(r);
    if r='' then break;
    n:=copy(r,1,6);
    p:=pos('.',r);
    if p<>0 then begin delete(n,p,1); p:=6-p; end else p:=0;
    for i:=1 to length(n) do rt[i]:=ord(n[i])-48;
    if p<>0 then len:=5 else len:=6;
    for i:=1 to (len shr 1) do begin t:=rt[i]; rt[i]:=rt[len-i+1]; rt[len-i+1]:=t;end;
    tl:=len;
    n:=copy(r,8,3);
    val(n,nt,e);
    if nt=0 then begin s[j]:='1'; continue; end;
    now:=rt;
    po:=p*nt;
    for i:=1 to nt-1 do times;
    p:=1;
    while (now[p]=0) and (p<=po) do inc(p);
    if po>len then begin s[j]:=s[j]+'.'; for i:=1 to po-len do s[j]:=s[j]+'0'; end;
    for i:=len downto p do 
    begin 
      if i=po then s[j]:=s[j]+'.';
      s[j]:=s[j]+chr(now[i]+48);
    end;  
    inc(j);
  end;  
  for i:=1 to j do writeln(s[i]);
end.
