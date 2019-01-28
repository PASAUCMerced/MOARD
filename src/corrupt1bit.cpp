#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Metadata.h"
//#include "llvm/DebugInfo.h"

#include <fstream>
#include <iostream>
#include <string>

#include "utility.h"

using namespace llvm;
using namespace std;

namespace{
  Value *f_dyn_counter = nullptr;
  Value *f_int_injection = nullptr;
  Value *f_dou_injection = nullptr;
  Value *v_ret_counter = NULL;
  Value *v_corr_data = NULL;
  
  int lineNum = 0;

  //int typeLabel = 0;// Integer:0/ Double,float,etc:1 
  struct corrupt1bit : public ModulePass {
	static char ID;
	corrupt1bit() : ModulePass(ID) {}
	virtual bool runOnModule(Module &M);
	Constant *createStringArg(char *string, Module &M);
  };
}

string val2str(Value *i){
  string s;
  raw_string_ostream rso(s);
  i->print(rso);
  return rso.str();
}

string inst2str(const Instruction *i){
  string s;
  raw_string_ostream rso(s);
  i->print(rso);
  return "{" + rso.str() + "}";
}


// convert Char* to Constant* for 'Log' function
Constant * corrupt1bit::createStringArg(char *string, Module &M) {
      
  Constant *v_string = ConstantDataArray::getString(M.getContext(), string, true);
  ArrayType *ArrayTy_0 = ArrayType::get(IntegerType::get(M.getContext(), 8), (strlen(string) + 1));
  GlobalVariable *gvar_array = new GlobalVariable(M, ArrayTy_0, true, GlobalValue::PrivateLinkage, 0, ".str");
  gvar_array->setAlignment(1);
  gvar_array->setInitializer(v_string);
  std::vector<Constant *> indices;
    
  ConstantInt *zero = ConstantInt::get(M.getContext(), APInt(32, StringRef("0"), 10));
   
  indices.push_back(zero);   
  indices.push_back(zero);
 
  //errs() << "SUCCESSFUL PASS!" << "\n";
  Type *ty = cast<PointerType>(gvar_array->getType()->getScalarType())->getElementType();
  Constant* const_ptr =  ConstantExpr::getGetElementPtr(ty, gvar_array, indices);
  return const_ptr;
}

bool corrupt1bit::runOnModule(Module &M)
{
/*==------------------------------------------------------------------------------==
 *== Read the existing fault site information from environment varialbes, these   ==
 *== environment variables are extract from each line of fault site files by      ==
 *== shell script or python script. Seven variables represent seven fields        ==
 *==------------------------------------------------------------------------------==*/
  
  char* work_func = getenv("WORK_FUNC");
  string _work_func(work_func);
 
  char* oprandID = getenv("OPRAND_ID");
  char* bitPosition = getenv("BIT_POSITION");
  char* dynInstrID = getenv("DYN_INSTR_ID");
  char* regName = getenv("REG_NAME");
  char* staticInstrID = getenv("STATIC_INSTR_ID");
  char* opcodeID = getenv("OPCODE_ID");

  int _oprandID = atoi(oprandID)-1;// NOTE:remember to update all the copies
  int _bitPosition = atoi(bitPosition);
  int _dynInstrID = atoi(dynInstrID);
  string _regName(regName);
  int _staticInstrID = atoi(staticInstrID);
  int _opcodeID = atoi(opcodeID);

  const char* _opcodeName = id2Name(_opcodeID);

  errs() << "Target Site Opcode ID: " << _opcodeID << "\n";
  errs() << "Target Site Opcode Name: " << _opcodeName << "\n";

/*==------------------------------------------------------------------------------==
 *== Get the current dynamic instruction ID to identify the fault injection site  ==
 *==------------------------------------------------------------------------------==*/
  int dyn_instr_counter = 0;
  Value *dyn_counter = ConstantInt::get(IntegerType::getInt32Ty(getGlobalContext()), dyn_instr_counter);

  for (Module::iterator F = M.begin(), e1 = M.end(); F!=e1; ++F){
    if (F->isDeclaration())
      continue;

    if (F->getName().str().find("functionDynInstCounter")!= string::npos)
    {
      f_dyn_counter = &(*F);
	  errs() << F->getName() <<"\n";
    }
	if (F->getName().str().find("intFaultInjection")!= string::npos)
	{
	  f_int_injection = &(*F);
	  errs() << F->getName() <<"\n";
	}
	if (F->getName().str().find("doubleFaultInjection")!= string::npos)
	{
	  f_dou_injection = &(*F);
	  errs() << F->getName() <<"\n";
	}

  }

  for (Module::iterator F = M.begin(), e1 = M.end(); F!=e1; ++F){
    if (F->isDeclaration())
	  continue;

    if (F->getName().str().find(_work_func)!= string::npos)
    {
	   errs() << F->getName() <<"\n";
	   for (Function::iterator bb = F->begin(), e = F->end(); bb != e; ++bb) {
         errs()<<"--------------------------------this is the separater for different BBs----------------------------\n";

         //-------------test by Anzheng-----------------------//
         errs()<<"bb info for the curr BB\n";
         for (BasicBlock::iterator inst = bb->begin(), e = bb->end(); inst != e; ++inst) {
             Instruction *II = dyn_cast<Instruction>(inst);
           errs()<<inst2str(II)<<"\n"; 
         }
         errs()<<"bb info for the curr BB\n";
         for (BasicBlock::iterator i = bb->begin(), e = bb->end(); i != e; ++i) {
		   if (Instruction *I = dyn_cast<Instruction>(i)){
			 errs()<<inst2str(I)<<"\n";

		     errs() <<"the opcode name is: " << I->getOpcodeName() <<"\n";
		     if (DebugLoc Loc = I->getDebugLoc())
			 //if (MDNode *N = I->getMetadata("dbg"))
			 {
			   //DILocation Loc(N);
			   //lineNum = Loc.getLineNumber();
			   lineNum = Loc.getLine();
			 }

			 errs() << "current line number is:  " << lineNum << "\n";
			 //lineNum = Loc.getLine();
		     errs() << "test0 -> " << lineNum <<"\n";
			 char* opcodeName = (char*)(I->getOpcodeName());
			 Constant* v_opName = createStringArg(opcodeName, M);
			 if (isa<CallInst>(I)){
			   // in order to match with LLVM-Tracer, here we temperorily ignore Call instruction
			   //std::string name = cast<CallInst>(I)->getCalledFunction()->getName();
			   //if (name.find("functionDynInstCounter") != string::npos){
			   //continue;
			   //}else{
			     //BasicBlock::iterator it(I);
			     //it++;
		         //Instruction *location = &(*(it));
		         //IRBuilder<> IRB(location);
				 //Value *args[] = {dyn_counter, v_opName};
				 //IRB.CreateCall(f_dyn_counter, args, "dynamic_instruction_counter");
			   //}
			 
			   continue;
			 }else{
			   if (I->getOpcode() == Instruction::PHI){
			     errs() << "test1" <<"\n";
			     BasicBlock::iterator it(I);
				 it++; 
				 Instruction *location = &(*(it));
				 IRBuilder<> IRB(location);
				 Value *args[] = {dyn_counter, v_opName};
				 v_ret_counter = IRB.CreateCall(f_dyn_counter, args, "dynamic_instruction_counter");
				 errs() << "The dynamic value of the returned counter is: " << val2str(v_ret_counter) << " " <<I->getOpcodeName()<<"\n";
				 errs() << "test2" <<"\n";
			   }else{
			     errs() << "test3" <<"\n";
			     IRBuilder<> IRB1(I);
				 Value *args[] = {dyn_counter, v_opName};
				 v_ret_counter = IRB1.CreateCall(f_dyn_counter, args, "dynamic_instruction_counter");
				 errs() << "The dynamic value of the returned counter is: " << val2str(v_ret_counter) << " " <<I->getOpcodeName()<< "\n";
				 errs() << "test4" <<"\n";
				 //DebugLoc Loc = I->getDebugLoc();
				 errs() << "test5" <<"\n";
				 
				 // pass the operand that to be corrupted to the corrupt function only when it meets 
				 // the following conditions. 
				 // pass to different corrupt functions according to the type of the operand.
				 //
				 errs() << "test6" <<"\n";
//-*-				 
				 const char* realTimeOpcdName = (char*)I->getOpcodeName();

				 string str_opcodename(_opcodeName);
				 string str_realopcodename(realTimeOpcdName);
				 if (_staticInstrID == lineNum){
				   errs() << "Success Line number: " << _staticInstrID << "\n";
				   errs() << "Real Time Opcode Name: " << realTimeOpcdName << "\n";
				   errs() << "Target Site Opcode Name: " << _opcodeName << "\n";
				   bool is = str_realopcodename == str_opcodename;
				   errs() << "whether the two opcodes are equal: "<< is << "\n";
				   if (str_realopcodename == str_opcodename){
				     errs() << "ALMOST SUCCESSED!" << "\n"; 
					 //Type iType = I->getType()->getTypeID();
					 if (I->getType()->getTypeID() == Type::IntegerTyID){
					   //typeLabel = 0;
					   Value* data = I->getOperand(_oprandID);
					   Value *_data = IRB1.CreateZExt(data, IRB1.getInt32Ty(), "zext1");
		               Constant *dynID = ConstantInt::get(IntegerType::getInt32Ty(getGlobalContext()), _dynInstrID);
					   Constant *bitID = ConstantInt::get(IntegerType::getInt32Ty(getGlobalContext()), _bitPosition);
					   Value *args1[] = {_data, dynID, bitID};
					   v_corr_data = IRB1.CreateCall(f_int_injection, args1, "int_fault_injection");
					   errs() <<"the corrpted value of the operand is: "<< val2str(v_corr_data) <<"\n";
					   I->setOperand(_oprandID, v_corr_data);

					 }else if ((I->getType()->getTypeID() == llvm::Type::HalfTyID)||(I->getType()->getTypeID() ==llvm::Type::FloatTyID)||(I->getType()->getTypeID() ==llvm::Type::DoubleTyID)||(I->getType()->getTypeID() ==llvm::Type::X86_FP80TyID)||(I->getType()->getTypeID() ==llvm::Type::FP128TyID)||(I->getType()->getTypeID() ==llvm::Type::PPC_FP128TyID)){
					   
					   Value* data = I->getOperand(_oprandID);
					   Value *_data = IRB1.CreateFPExt(data, IRB1.getDoubleTy(), "fpExt");
				 	   //errs() << "IS IT DOUBLE TYPE? : " << _data->getType()->getTypeID() << "\n";
					   Constant *dynID = ConstantInt::get(IntegerType::getInt32Ty(getGlobalContext()), _dynInstrID);
					   Constant *bitID = ConstantInt::get(IntegerType::getInt32Ty(getGlobalContext()), _bitPosition);
					   Value *args1[] = {_data, dynID, bitID};
					   v_corr_data = IRB1.CreateCall(f_dou_injection, args1, "double_fault_injection");
					   errs() <<"the corrpted value of the operand is: "<< val2str(v_corr_data) <<"\n";
					   I->setOperand(_oprandID, v_corr_data);
					   }
				   } 
				 }
//-*-			 
				 //errs() << "test4" <<"\n";
			   }
			 }
		   }
		   //const Instruction* inst = &(*i);
		   //errs()<<inst2str(inst)<<"\n";
         }
	   }
    }
  }
    //errs() << "Function " << F.getName() << '\n';
  return false;
}
 
  

char corrupt1bit::ID = 0;
static RegisterPass<corrupt1bit> X("Corruption", "LLVM Pass: Corrupting one bit in specified varialbe");
