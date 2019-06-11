program hybz1930;
var n,i:longint;
    c:array[1..3,0..10000]of longint;
    a,b:array[1..10000]of longint;

function find(d,x:longint):longint;
var l,r,mid:longint;
begin
  l:=0;
  r:=c[d,0]+1;
  while l+1<r do
  begin
    mid:=(l+r)>>1;
    if c[d,mid]>x then r:=mid else l:=mid;
  end;
  exit(r);
end;

procedure insert(d,x:longint);
var p:longint;
begin
  if d=3 then exit;
  p:=find(d,x);
  if p<=c[d,0]then insert(d+1,c[d,p]);
  c[d,p]:=x;
  if p>c[d,0]then inc(c[d,0]);
end;

procedure swap(var x,y:longint);
var t:longint;
begin
  t:=x;
  x:=y;
  y:=t;
end;

procedure quicksort(l,r:longint);
var x,i,j,y:longint;
begin
  i:=l;
  j:=r;
  x:=random(r-l+1)+l;
  y:=b[x];
  x:=a[x];
  repeat
    while(a[i]<x)or((a[i]=x)and(b[i]<y))do inc(i);
    while(a[j]>x)or((a[j]=x)and(b[j]>y))do dec(j);
    if i<=j then
    begin
      swap(a[i],a[j]);
      swap(b[i],b[j]);
      inc(i);
      dec(j);
    end;
  until i>j;
  if i<r then quicksort(i,r);
  if j>l then quicksort(l,j);
end;

begin
  readln(n);
  for i:=1 to n do readln(a[i],b[i]);
  quicksort(1,n);
  for i:=1 to n do insert(1,b[i]);
  writeln(c[1,0]+c[2,0]);
end.
