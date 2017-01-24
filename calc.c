    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <stdio.h>

    int powh(int x, int n){ //helper method since we can't include math.h
       
        int num = 1;
        for (int i = 0; i < n; ++i){
            num *= x;
        }
        return num;
    }

    void reverse(char * in){
           int length=strlen(in);
            int start=0;
           if(in[0]=='-'){
               start+=1;
           }
           int end=length-1;
           char temp;
           while(start<end){
               temp=in[start];
               in[start]=in[end];
               in[end]=temp;
               start++;
               end--;
           }
    }

    //convert everything to int, do operator, convert to output base and output

    int toInt(char * convert){ //still need to take into consideration -s
        int output = 0;
        
        if (convert[0] == 'd' || (convert[0] == '-' && convert[1] == 'd')){ //convert decimal to int
            char * toConvert = malloc (strlen(convert)); //don't need + 1 because youre not copying the first char anyways

           // int length = strlen(convert);
            if (convert[0] == 'd'){
                strncpy(toConvert, convert+1, strlen(convert)); //gets rid of first char and copies it to the string (toConvert)
            } else if (convert [0] == '-'){
                strncpy(toConvert, convert+2, strlen(convert));
            }
            
            int out = 0;
            int index = 0;
            while (index < strlen(toConvert)){
                if(!isdigit(toConvert[index])){
                    fprintf(stderr,"ERROR: Invalid decimal input");
                    exit(0);
                }
                out = out * 10 + (toConvert[index] - '0');
                index++;
            }
            if (convert[0] == '-'){ //it it's negative, have it output as -
                out = out * -1;
            }
            
            free(toConvert);
            return out;
            
        }
        else if (convert[0] == 'b' || (convert[0] == '-' && convert[1] == 'b')){ //convert binary to int
            
            char * toConvert = malloc (strlen(convert)); //don't need + 1 because youre not copying the first char anyways
            
            if (convert[0] == 'b'){
                strncpy(toConvert, convert+1, strlen(convert)); //gets rid of first char and copies it to the string (toConvert)
            } else if (convert [0] == '-'){
                strncpy(toConvert, convert+2, strlen(convert));
            }
            
            int out = 0;
            int index = 0;
            while (index < strlen(toConvert)){
                if(toConvert[index] != '0' && toConvert[index] != '1'){
                    fprintf(stderr,"ERROR: Invalid binary input");
                    exit(0);
                }
                out = out * 2 + (toConvert[index] - '0');
                index++;
            }
            if (convert[0] == '-'){ //it it's negative, have it output as -
                out = out * -1;
            }
            free (toConvert);
            return out;
            
            
        }
        else if (convert[0] == 'o' || (convert[0] == '-' && convert[1] == 'o')){//convert octal to int
           
            char * toConvert = malloc (strlen(convert)); //don't need + 1 because youre not copying the first char anyways
            
            if (convert[0] == 'o'){
                strncpy(toConvert, convert+1, strlen(convert)); //gets rid of first char and copies it to the string (toConvert)
            } else if (convert [0] == '-'){
                strncpy(toConvert, convert+2, strlen(convert));
            }
            
            int out = 0;
            int index = 0;
            while (index < strlen(toConvert)){
                int cur = toConvert[index] - '0';
                if(!isdigit(toConvert[index]) && cur > 7 ){
                    fprintf(stderr,"ERROR: Invalid octal input");
                    exit(0);
                }
                out = out * 8 + (toConvert[index] - '0');
                index++;
            }
            if (convert[0] == '-'){ //it it's negative, have it output as -
                out = out * -1;
            }
            free(toConvert);
            return out;
            
        }
        else if (convert[0] == 'x' || (convert[0] == '-' && convert[1] == 'x') ){ //hexadecimal to int
            //need a long for hexadecimals
            char * hex = malloc (strlen(convert)); //don't need + 1 because youre not copying the first char anyways
            if (convert[0] == 'x'){
                strncpy(hex, convert+1, strlen(convert)); //you don't need atoih here because hex will be a char * since it has letters
            } else if (convert[0] == '-'){
                strncpy(hex, convert+2, strlen(convert));
            }
            
            char values [16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}; //made 22 so it would work for upper case and lower case
            
            int j , count = 0;
            for (int i = strlen(hex) - 1; i>= 0; i--){
                for (j = 0; j < 16; j++){ //have to keep resetting j otherwise it doesn't keep going
                    if (hex[i] == values[j]){
                        output += j*powh(16, count);
                    }
                }
                count++;
            }
            if (convert[0] == '-'){
                output = output * -1;
            }
            free(hex);
            
        } else {
            fprintf(stderr,"ERROR: Your input for either num1 or num2 is not correct.");
            exit(0);
        }
        
        
        
        
        return output;
    }

    char * toBinary (int x){ //converting decimal to binary
        int r; //remainder
        char * out = malloc(34 * sizeof(char));
        int index = 0;
       /*if ( x < 0){
            out[0] = '-';
            out [1] = 'b';
            index = 2;
            x = x * -1;
        } else if (x > 0){
            out[0] = 'b';
            index = 1;
        } else {
            out[0] = 'b';
            out[1] = '0';
            index = 2;
        }*/
        
        int binary = 0, i = 1;
        while (x != 0){
            r = x%2;
            x = x/2;
            binary = binary + (r *i);
            i = i*10;
            out[index] = r + '0';
            index++;
        }
        //printf("\nout: %s", out);
        reverse(out);
        return out;
    }

    char * toOctal(int x){//converting decimal to octal
        int index=0;
        char * out = malloc(34 * sizeof(char));
        if ( x < 0){
            out[0] = '-';
            out [1] = 'o';
            index = 2;
            x = x * -1;
        } else {
            out[0] = 'o';
            index = 1;
        }
        int digit = 0;
        char  add = 'a';
        while (x != 0){
            digit = x%8;
            add = digit + '0';
            out [index] = add;
            index ++;
            x = x/8;
           
        }
        reverse(out);
        return out;
        
    }

    char * toHex (int x){//converting decimal to hex
        int hold = x; //placeholder
        if (x < 0){
            x = x * -1;
        }
        if (x == 0){ //special case when x = 0
            return "0";
        }
        
        char out [100]; //can use 100 since input will be less than 32 bits
        //char *re = malloc (100);
        char an [100];
        int i = 1, j, temp;
        while (x != 0){
            temp = x % 16;
            //int to char
            if (temp < 10){
                temp = temp + 48;
            } else { //for letters
                temp = temp + 55;
            }
            out[i++] = temp;
            x = x/16;
        }
        int k = 0;
        for (j = i - 1; j > 0; j--){
            an[k] =  out[j];
            k++;    
        }
an[k] = '\0';
        char * output = malloc(100);
        if (hold > 0){
            output[0] = 'x';
        } else if(hold < 0){
            output [0] = '-';
            output [1] = 'x';
        }
        
        strcpy(output, an);
       // strcat(output, '\0');
       return output;
    }

    char * toDecimal (int x){
        int i = 0;
        char * output = malloc (sizeof(char) * 32);
        if (x < 0){
            output[0] = '-';
            x = x * -1;
            i = 1;
        }
        //converting int to string
        while (x != 0){
            output[i] = x % 10 + '0';
            x = x /10;
            i++;
        }
        reverse(output);
        return output;
    }

    int main (int argc, char ** argv){
        
        char * op =argv[1];
        char * num1 = argv[2];
        char * num2 =argv[3];
        char * ob = argv[4]; //output base
        
        int result = 0;
       
        if (strcmp(op, "+") == 0){
            result = toInt(num1) + toInt(num2);
        } else if (strcmp(op , "-") == 0){
            result = toInt(num1) - toInt(num2);
        } else if (strcmp(op ,"*") == 0){
            result = toInt(num1) * toInt(num2);
        } else {
            fprintf(stderr,"ERROR: Invalid operation");
            exit(0);
        }
        
        int out = 0;
        if (strcmp(ob, "d") == 0){
            if (result < 0){
                out = result * -1;
                char * outd = toDecimal(out);
                printf("\n-d%s\n", outd);
            } else{
                char * outd = toDecimal(result);
                printf("\nd%s\n", outd);
            }
        } else if (strcmp(ob , "b") == 0){
            if (result < 0){
                out = result * -1;
                char * outp = toBinary(out);
                printf("\n-b%s\n", outp);
            } else {
                char * bina = toBinary(result);
                printf("\nb%s\n", bina);
            }
        } else if (strcmp(ob , "o") == 0){
            if (result < 0){
                char * octal = toOctal(result);
                out = out * -1;
                printf("\n%s\n", octal);
            } else {
                char * octal = toOctal(result);
                printf("\no%s\n", octal);
            }
        } else if (strcmp(ob , "x") == 0){
            if (result < 0){ 
                char * hexO = toHex(result); //result
                printf("\n-x%s\n", hexO);
            }
            else {
                char * hexOutput = toHex(result);
                printf("\nx%s\n",hexOutput );
            }
        } else {
            fprintf(stderr,"ERROR: Invalid output base");
            exit(0);

        }

        return 0;
    }

    //gcc -Wall -g -o


