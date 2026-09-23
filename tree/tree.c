   67                                                                                                             
   68   //Eliminar el nodo hoja                                                                                   
   69   if (raiz == NULL ) {                                                                                      
   70   │ return  NULL;                                                                                           
   71   }                                                                                                         
   72                                                                                                             
   73   if(dato < raiz->dato) {                                                                                   
   74   │ raiz->izq = Eliminar(raiz->izq, dato);                                                                  
   75   }                                                                                                         
   76   else if (dato > raiz->dato) {                                                                             
   77   │ raiz->der = Eliminar(raiz->der, dato);                                                                  
   78   }                                                                                                         
   79   else{                                                                                                     
   80   │ //Encontrar el nodo a Eliminar                                                                          
   81   │ if (raiz->izq == NULL) {                                                                                
   82   │ │ struct Nodo * temp = raiz->der;                                                                       
   83   │ │ free(raiz);                                                                                           
   84   │ │ return temp;                                                                                          
   85   │ }                                                                                                       
   86   │ else if(raiz->der == NULL){                                                                             
   87   │ │ struct Nodo * temp = raiz->izq;                                                                       
   88   │ │ free(raiz);                                                                                           
   89   │ │ return temp;                                                                                          
   90   │ }                                                                                                       
   91   │                                                                                                         
   92   │ //Caso de dos hijos                                                                                     
   93   │ struct Nodo * temp = ObtenerMinimo(raiz->der);                                                          
   94   │ raiz->dato = temp->dato;                                                                                
   95   │ raiz->der = Eliminar(raiz->der, temp->dato);                                                            
   96   }                                                                                                         
   97                                                                                                             
   98   return raiz;                                                                                              
   99                                                                                                             
  100 }                                                                                                           
  101 int main(void)                                                                                              
  102 {                                                                                                           
  103 │ struct Nodo * raiz = NULL;                                                                                
  104 │ raiz = Insertar(raiz, 50);                                                                                
  105 │ raiz = Insertar(raiz, 30);                                                                                
  106 │ raiz = Insertar(raiz, 70);                                                                                
  107 │ raiz = Insertar(raiz, 20);                                                                                
  108 │ raiz = Insertar(raiz, 40);                                                                                
  109 │ raiz = Insertar(raiz, 60);                                                                                
  110 │ raiz = Insertar(raiz, 80);                                                                                
  111 │ inOrder(raiz);                                                                                            
  112 │ printf("\n");                                                                                             
  113 │ raiz = Eliminar(raiz, 20);                                                                                
  114 │ raiz = Eliminar(raiz, 50);                                                                              
  115 │ inOrder(raiz);                                                                       
  116 │ printf("\n");                                                                        
  117 │ liberarArbol(raiz);                                                                  
  118 │ return EXIT_SUCCESS;                                                                 
  119 }                                                                                      
  INSERT  tree.c                                                        LSP ~ clangd 󰉋  punteros   119/2 
No signature help available                                                                                       
