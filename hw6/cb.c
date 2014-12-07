CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{
  int bsize = size;
  if(size & (size-1)) 
  {
    bsize=size+1; //adjust size to be a power of 2
  }
  int sz = bsize*sizeof(KeyType)+sizeof(CircularBuffer);
  *pQue = (CircularBuffer*) malloc(sz);
  if(*pQue)
  {
    (*pQue)->writePointer = 0;
    (*pQue)->readPointer  = 0;
    (*pQue)->size=size;
    (*pQue)->mask=size-1; 
  }
  return *pQue;
}
 
inline int CircularBufferIsFull(CircularBuffer* que)
{
  return (((que->writePointer + 1) & que->mask) == que->readPointer); 
}
 
inline int CircularBufferIsEmpty(CircularBuffer* que)
{
  return (que->readPointer == que->writePointer); 
}
 
inline int CircularBufferEnque(CircularBuffer* que, KeyType k)
{
  int isFull = CircularBufferIsFull(que);
  if(!isFull) 
  {
    que->keys[que->writePointer] = k;
    que->writePointer++;
    que->writePointer &= que->mask;
  }
  return isFull;
}
 
inline int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{
  int isEmpty =  CircularBufferIsEmpty(que);
  if(!isEmpty) 
  {
    *pK = que->keys[que->readPointer];
    que->readPointer++;
    que->readPointer &= que->mask;
  }
  return(isEmpty);
}
 
inline int CircularBufferPrint(CircularBuffer* que)
{
  int i=0;
  int isEmpty =  CircularBufferIsEmpty(que);
  int isFull  =  CircularBufferIsFull(que);
  printf("\n==Q: w:%d r:%d f:%d e:%d\n", 
    que->writePointer, que->readPointer,  isFull, isEmpty);
  for(i=0; i< que->size; i++)
  {
   printf("%d ", que->keys[i]);
  }
  printf("\n");
  return(isEmpty);
}
