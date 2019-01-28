#include "stdio.h"
#include "utility.h"

const char* id2Name(int _opcodeID){
   const char* _opcodeName = nullptr;

   switch(_opcodeID){
     case 0: 
       _opcodeName = "move";
       break;
     case 1: 
       _opcodeName = "ret";
       break;
     case 2:
       _opcodeName = "br";
       break;
     case 3:
       _opcodeName = "switch";
       break;
     case 4:
       _opcodeName = "indirectbr";
       break;
     case 5:
       _opcodeName = "invoke";
       break;
     case 6:
       _opcodeName = "resume";
       break;
     case 7:
       _opcodeName = "unreachable";
       break;
     case 8:
       _opcodeName = "add";
       break;
     case 9:
       _opcodeName = "fadd";
       break;
     case 10:
       _opcodeName = "sub";
       break;
     case 11:
       _opcodeName = "fsub";
       break;
     case 12:
       _opcodeName = "mul";
       break;
     case 13:
       _opcodeName = "fmul";
       break;
     case 14:
       _opcodeName = "udiv";
       break;
     case 15:
       _opcodeName = "sdiv";
       break;
     case 16:
       _opcodeName = "fdiv";
       break;
     case 17:
       _opcodeName = "urem";
       break;
     case 18:
       _opcodeName = "srem";
       break;
     case 19:
       _opcodeName = "frem";
       break;
     case 20:
       _opcodeName = "shl";
       break;
     case 21:
       _opcodeName = "lshr";
       break;
     case 22:
       _opcodeName = "ashr";
       break;
     case 23:
       _opcodeName = "and";
       break;
     case 24:
       _opcodeName = "or";
       break;
     case 25:
       _opcodeName = "xor";
       break;
     case 26:
       _opcodeName = "alloca";
       break;
     case 27:
       _opcodeName = "load";
       break;
     case 28:
       _opcodeName = "store";
       break;
     case 29:
       _opcodeName = "getelementptr";
       break;
     case 30:
       _opcodeName = "fence";
       break;
     case 31:
       _opcodeName = "atomiccmpxchg";
       break;
     case 32:
       _opcodeName = "atomicrmw";
       break;
     case 33:
       _opcodeName = "trunc";
       break;
     case 34:
       _opcodeName = "zext";
       break;                                    
     case 35:
       _opcodeName = "sext";
       break;
     case 36:
       _opcodeName = "fptoui";
       break;
     case 37:
       _opcodeName = "fptosi";
       break;
     case 38:
       _opcodeName = "uitofp";
       break;        
     case 39:
       _opcodeName = "sitofp";
       break;  
     case 40:
       _opcodeName = "fptrunc";
       break;  
     case 41:
       _opcodeName = "fpext";
       break;  
     case 42:
       _opcodeName = "ptrtoint";
       break;  
     case 43:
       _opcodeName = "inttoptr";
       break;
     case 44:
       _opcodeName = "bitcast";
       break;
     case 45:
       _opcodeName = "addrspacecast";
       break;
     case 46:
       _opcodeName = "icmp";
       break;        
     case 47:
       _opcodeName = "fcmp";
       break;
     case 48:
       _opcodeName = "phi";
       break;
     case 49:
       _opcodeName = "call";
       break;
     case 50:
       _opcodeName = "select";
       break;        
     case 53:
       _opcodeName = "vaarg";
       break;
     case 54:
       _opcodeName = "extractelement";
       break;
     case 55:
       _opcodeName = "insertelement";
       break;
     case 56:
       _opcodeName = "shufflevector";
       break;
     case 57:
       _opcodeName = "extractvalue";
       break;
     case 58:
       _opcodeName = "insertvalue";
       break;
     case 59:
       _opcodeName = "landingpad";
       break;
     case 98:
       _opcodeName = "dmastore";
       break;
     case 99:
       _opcodeName = "dmaload";
       break;
     case 100:
       _opcodeName = "indexadd";
       break;
     case 101:
       _opcodeName = "silentstore";
       break;
     default:
       printf("A new opcode is found to be excluded from this list!!");
  }
  return _opcodeName;
}
