#include<iostream>
using namespace std;

void djikistra(int);

int main() {
    cout<< "\n\nᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ˖ ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ★"
            "\n\n⊹\t\t  /\\_/\\                                type     ★"
            "\n\n★\t\t (  .ω.)   ____    type                         ⊹"
            "\n\nᯓ\t\t  |  つ__/     /             type               ★" 
        <<" \n\n𖥔\t\t                                                𖥔"
        <<" \n\n⊹\t\tWELCOME TO MY HEAP COMPLEXITY ANALYSER          ★"
        <<" \n\n★\t\t                                                ⊹"
        <<" \n\nᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ";
    
    cout<<"\n\n ᯓ݁˖ 𖥔.ᯓ  DATASET SELECTION   ᯓ.𖥔 ݁ ˖ ᯓ݁"
        <<"\n(1) Chongqing Road Data"
        <<"\n(2) Hong Kong Road Data"
        <<"\n(3) Shanghai Road Data"
        <<"\n(0) Exit";
    int op;
    cin>>op;

    switch(op) {
        case 1:

            //djikistra(1);
            break; 
        case 2:
            //djikistra(2);
            break;
        case 3:
            //djikistra(3);
            break;
        case 0:
            cout<<"\n\nGoodbye! ᯓ.𖥔 ݁ ˖ ᯓ"<<endl<<endl;
            break;
        default:
            cout<<"\nInvalid option! Exiting ... "<<endl<<endl;
            break;
    }
    return 0;
}

void djikistra(int dataset) {

}