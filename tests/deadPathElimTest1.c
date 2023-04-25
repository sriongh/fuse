#pragma fuse seq(ccs, cp, dp, cp)

#define __VERIFIER_error CompDebugAssert

void CompDebugAssert(int e) { }

void calculate_output(int);
void calculate_outputm53(int);


int a72 = 13;

void calculate_outputm53(int input) {
}

void calculate_output(int input) {
  if(a72 == 12) {
    calculate_outputm53(input);
  }
}

int main() {
  calculate_output(2);
}

