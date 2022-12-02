#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#define SIZE 1000

FILE *pacientesArq;
FILE *pacientesGeraisArq;
FILE *grupoRiscoArq;
int operacaoMenuInicial, operacaoSalvarCadastro, operacaoExibirDados, operacaoComorbidade;
int operacaoInformacoesSistemas, operacaoConfirmarExcluir, operacaoExcluirDados, operacaoProximoPaciente;
int qtdDiasIdade, qtdMesesIdade, qtdAnosIdade;
char texto[1000], t, numeroChar[200];;
int ultimoIdPacientesGerais = 0, ultimoIdGrupoRisco = 0, i = 0, linhas = 0, limiteLinhas = 28, o, numeros = 0;

struct tm *dataAtual;
time_t segundos;

struct ficha_endereco{
    char rua[100], bairro[40], cidade[40], estado[30], cep[20], numero[20];
};
struct ficha_dataNascimento{
    int dia, mes, ano;
};
struct ficha_dataDiagnostico{
    int dia, mes, ano;
};
struct ficha_paciente{
    char nome[50], email[50], comorbidadepaciente[200], cpf[20], telefone[20];

    struct ficha_endereco endereco;
    struct ficha_dataNascimento dataNascimento;
    struct ficha_dataDiagnostico dataDiagnostico;
} paciente[SIZE];

void main(){
    setlocale(LC_ALL, "Portuguese");
    SetConsoleTitle("SISTEMA DE CADASTRO COVID-19");
    system("mode con:cols=62 lines=40");
    validacaoLogin();
    sistemaPrincipal();
}

void sistemaPrincipal(){
    operacaoMenuInicial = 444;
    while(operacaoMenuInicial != 0){
        painelMenuInicial();
        switch(operacaoMenuInicial){
            case 5:
                return 1;
            case 1:
                cadastrarPaciente();
                break;
            case 2:
                exibirDados();
                break;
            case 3:
                excluirDados();
                break;
            case 4:
                informacoesSistemas();
                break;
            case 0:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
            default:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
        }
    }
    sistemaPrincipal();
}

void painelBemVindo(){

    system("mode con:cols=55 lines=10");
    printf("|\t\t\t\t\t\t\t|\n");
    printf("|\tBEM VINDO AO SISTEMA DE CADASTRO COVID-19\t|\n");
    printf("|_____________________________________________________|\n\n");
}
void validacaoLogin(){
    char loginSistema[20] = "admin";
    char loginDigitado[20];
    char senhaSistema[20] = "admin";
    char senhaDigitada[20];

    painelBemVindo();

    int login_efetuado = 0;

    while(!login_efetuado){
        printf("\n\nDIGITE O LOGIN: ");
        fflush(stdin);
        gets(loginDigitado);

        printf("DIGITE A SENHA: ");
        fflush(stdin);
        gets(senhaDigitada);

        if(strcmp(loginSistema, loginDigitado) == 0 && strcmp(senhaSistema, senhaDigitada) == 0){
            login_efetuado = 1;
        }
        else{
            system("cls");
            painelBemVindo();
            printf("DADOS INVALIDOS!\n");
        }
    }
}

void painelMenuInicial(){
        system("mode con:cols=100 lines=28");
        system("cls");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tMENU INCIAL\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|_______________________________________________________________________________________________|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t1-CADASTRAR\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t2-EXBIR DADOS\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t3-EXCLUIR DADOS\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t4-INFORMAÇÕES DO SISTEMA\t\t\t\t\t|\n");
        printf("|\t\t\t\t5-SAIR\t\t\t\t\t\t\t\t|\n");
        printf("|_______________________________________________________________________________________________|\n\n\n");
        printf("DIGITE O NUMERO DA OPÇÃO QUE DESEJAR: ");
        operacaoMenuInicial = validaNumerosCaracteres(operacaoMenuInicial);
}

void cadastrarPaciente(){
    system("mode con:cols=100 lines=30");
    system("cls");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|__________________________PREENCHA OS DADOS DO PACIENTE________________________________________|\n\n");

    pacientesGeraisArq = fopen("cache/contagem_pacientes_diagnosticados.txt", "r");
    fscanf(pacientesGeraisArq, "%d", &ultimoIdPacientesGerais);
    fclose(pacientesGeraisArq);

    grupoRiscoArq = fopen("cache/contagem_grupo_de_risco.txt", "r");
    fscanf(grupoRiscoArq, "%d", &ultimoIdGrupoRisco);
    fclose(grupoRiscoArq);

    while(i <= ultimoIdPacientesGerais || i <= ultimoIdGrupoRisco){
       i++;
    }
    printf("NOME COMPLETO............: ");
    validaApenasLetras(paciente[i].nome);
    if(t!=27){
        printf("\nCPF......................: ");
        validaApenasNumeros(paciente[i].cpf);
    }
    if(t!=27){
        printf("\nDATA DE NASCIMENTO ");
        printf("\nDIA......................: ");
        paciente[i].dataNascimento.dia = validaNumerosCaracteres(paciente[i].dataNascimento.dia);
    }
    if(t!=27){
        printf("MES......................: ");
        paciente[i].dataNascimento.mes = validaNumerosCaracteres(paciente[i].dataNascimento.mes);
    }
        if(t!=27){
        printf("ANO......................: ");
        paciente[i].dataNascimento.ano = validaNumerosCaracteres(paciente[i].dataNascimento.ano);
    }
    if(t!=27){
        while(validarData(paciente[i].dataNascimento.dia, paciente[i].dataNascimento.mes, paciente[i].dataNascimento.ano) != 1 && t!=27){
            system("cls");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|__________________________PREENCHA OS DADOS DO PACIENTE________________________________________|\n\n");
            printf("\nDATA INVÁLIDA!\n\n");
            if(t!=27){
                printf("\nDATA DE NASCIMENTO:");
                printf("\nDIA......................: ");
                paciente[i].dataNascimento.dia = validaNumerosCaracteres(paciente[i].dataNascimento.dia);
            }
            if(t!=27){
                printf("MES......................: ");
                paciente[i].dataNascimento.mes = validaNumerosCaracteres(paciente[i].dataNascimento.mes);
            }
            if(t!=27){
                printf("ANO......................: ");
                paciente[i].dataNascimento.ano = validaNumerosCaracteres(paciente[i].dataNascimento.ano);
            }
        }
        calcularIdade(paciente[i].dataNascimento.dia, paciente[i].dataNascimento.mes, paciente[i].dataNascimento.ano);

    }
    if(t!=27){
        printf("\nTELEFONE.................: ");
        validaApenasNumeros(paciente[i].telefone);
    }
    if(t!=27){
        printf("\nE-MAIL...................: ");
        validaCaractere(paciente[i].email);
    }
    if(t!=27){
        while(validarEmail(paciente[i].email) != 1 && t!=27){
            system("cls");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|__________________________PREENCHA OS DADOS DO PACIENTE________________________________________|\n\n");
            if(t!=27){
                printf("\nE-MAIL INVÁLIDO!\n\n");
                printf("\nE-MAIL...................: ");
                validaCaractere(paciente[i].email);
            }
        }
    }
    if(t!=27){
        system("cls");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        if(t!=27){
            printf("|_____________________PREENCHA OS DADOS DE ENDEREÇO DO PACIENTE_________________________________|\n\n");
            printf("RUA......................: ");
            validaCaractere(paciente[i].endereco.rua);
        }
    }
    if(t!=27){
        printf("\nNÚMERO...................: ");
        validaApenasNumeros(paciente[i].endereco.numero);
    }
    if(t!=27){
        printf("\nBAIRRO...................: ");
        validaCaractere(paciente[i].endereco.bairro);
    }
    if(t!=27){
        printf("\nCIDADE...................: ");
        validaApenasLetras(paciente[i].endereco.cidade);
    }
    if(t!=27){
        printf("\nESTADO...................: ");
        validaApenasLetras(paciente[i].endereco.estado);
    }
    if(t!=27){
        printf("\nCEP......................: ");
        validaApenasNumeros(paciente[i].endereco.cep);
    }
    if(t!=27){
        system("cls");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|___________________PREENCHA OS DADOS DO DIAGNOSTICO DO PACIENTE________________________________|\n\n");

        printf("\nDATA DO DIAGNOSTICO ");
        printf("\nDIA......................: ");
        paciente[i].dataDiagnostico.dia = validaNumerosCaracteres(paciente[i].dataDiagnostico.dia);
    }
    if(t!=27){
        printf("MES......................: ");
        paciente[i].dataDiagnostico.mes = validaNumerosCaracteres(paciente[i].dataDiagnostico.mes);
    }
    if(t!=27){
        printf("ANO......................: ");
        paciente[i].dataDiagnostico.ano = validaNumerosCaracteres(paciente[i].dataDiagnostico.ano);
    }
    if(t!=27){
        while(validarData(paciente[i].dataDiagnostico.dia, paciente[i].dataDiagnostico.mes, paciente[i].dataDiagnostico.ano) != 1 && t!=27){
            system("cls");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t[APERTE > ESC < PARA CANCELAR O CADASTRO]\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
            printf("|___________________PREENCHA OS DADOS DO DIAGNOSTICO DO PACIENTE________________________________|\n\n");
            printf("\nDATA INVÁLIDA!\n\n");
            if(t!=27){
                printf("\nDATA DO DIAGNOSTICO:");
                printf("\nDIA......................: ");
                paciente[i].dataDiagnostico.dia = validaNumerosCaracteres(paciente[i].dataDiagnostico.dia);
            }
            if(t!=27){
                printf("MES......................: ");
                paciente[i].dataDiagnostico.mes = validaNumerosCaracteres(paciente[i].dataDiagnostico.mes);
            }
            if(t!=27){
                printf("ANO......................: ");
                paciente[i].dataDiagnostico.ano = validaNumerosCaracteres(paciente[i].dataDiagnostico.ano);
            }
        }
    }
    if(t!=27){
        printf("\nO PACIENTE POSSUI ALGUMA COMORBIDADE? ");
        printf("\nDIGITE > 1 < PARA SIM OU > 2 < PARA NÃO: ");
        operacaoComorbidade = validaNumerosCaracteres(operacaoComorbidade);
    }
    if(t!=27){
        while(operacaoComorbidade != 1 && operacaoComorbidade != 2 && t!=27){
            system("cls");
            printf("\n\nOPÇÃO INVÁLIDA!\n\n");
            if(t!=27){
                printf("\nO PACIENTE POSSUI ALGUMA COMORBIDADE? ");
                printf("\nDIGITE > 1 < PARA SIM OU > 2 < PARA NÃO: ");
                operacaoComorbidade = validaNumerosCaracteres(operacaoComorbidade);
            }
        }
    }
    if(t!=27){
        if(operacaoComorbidade == 1){
            if(t!=27){
                printf("\nDIGITE AS COMORBIDADES DO PACIENTE: ");
                validaCaractere(paciente[i].comorbidadepaciente);
            }
        }else{
            printf("\nO PACIENTE NÃO POSSUI COMORBIDADES.");
        }
    }
    if(t!=27){
        system("cls");
        system("mode con:cols=100 lines=42");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tFICHA DE CADASTRO\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|___________________CONFIRME OS DADOS DO DIAGNOSTICO DO PACIENTE________________________________|\n\n");

        printf("DADOS PESSOAIS:\n\n");
        printf("ID......................: %d", i);
        printf("\nNOME DO PACIENTE........: %s", paciente[i].nome);
        printf("\nCPF.....................: %s", paciente[i].cpf);
        printf("\nDATA DE NASCIMENTO......: %2.2d/%2.2d/%4.4d", paciente[i].dataNascimento.dia, paciente[i].dataNascimento.mes, paciente[i].dataNascimento.ano);
        printf("\nTELEFONE................: %s", paciente[i].telefone);
        printf("\nE-MAIL..................: %s", paciente[i].email);
        printf("\n------------------------------------------------------------------------------------------------");
        printf("\n\nLOGRADOURO:\n\n");
        printf("RUA.....................: %s", paciente[i].endereco.rua);
        printf("\nNÚMERO..................: %s", paciente[i].endereco.numero);
        printf("\nBAIRRO..................: %s", paciente[i].endereco.bairro);
        printf("\nCIDADE..................: %s", paciente[i].endereco.cidade);
        printf("\nESTADO..................: %s", paciente[i].endereco.estado);
        printf("\nCEP.....................: %s", paciente[i].endereco.cep);
        printf("\n------------------------------------------------------------------------------------------------");
        printf("\n\nDADOS DO DIAGNOSTICO DO PACIENTE:\n");
        printf("\nDATA DO DIAGNOSTICO.....: %2.2d/%2.2d/%4.4d", paciente[i].dataDiagnostico.dia, paciente[i].dataDiagnostico.mes, paciente[i].dataDiagnostico.ano);
        if(operacaoComorbidade == 1){
            printf("\nCOMORBIDADES DO PACIENTE: %s\n", paciente[i].comorbidadepaciente);
        }else{
            printf("\nCOMORBIDADES DO PACIENTE: O PACIENTE NÃO POSSUI COMORBIDADES.\n");
        }
        printf("\n_________________________________________________________________________________________________\n");

        printf("\n\nDIGITE > 1 < PARA SALVAR O CADASTRO OU > 2 < PARA RETORNAR AO MENU. \n");
        operacaoSalvarCadastro = validaNumerosCaracteres(operacaoSalvarCadastro);

        while(operacaoSalvarCadastro != 1 && operacaoSalvarCadastro != 2){
                system("cls");
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("DIGITE > 1 < PARA SALVAR O CADASTRO OU > 2 < PARA RETORNAR AO MENU.\n");
                operacaoSalvarCadastro = validaNumerosCaracteres(operacaoSalvarCadastro);
        }

        if(operacaoSalvarCadastro == 1){
            if(operacaoComorbidade == 1 || qtdAnosIdade >= 65){
                pacientesArq = fopen("pacientes do grupo de risco/grupo_de_risco.txt", "a");
                grupoRiscoArq = fopen("cache/contagem_grupo_de_risco.txt", "w");

                if(pacientesArq == NULL || grupoRiscoArq == NULL){
                    printf("ERRO NA ABERTURA DO ARQUIVO!");
                    return 1;
                }else{
                    fprintf(grupoRiscoArq, "%d", i);
                    fclose(grupoRiscoArq);
                }
            }else{
                pacientesArq = fopen("pacientes fora do grupo de risco/pacientes_diagnosticados.txt", "a");
                pacientesGeraisArq = fopen("cache/contagem_pacientes_diagnosticados.txt", "w");

                if(pacientesArq == NULL || pacientesGeraisArq == NULL){
                    printf("ERRO NA ABERTURA DO ARQUIVO!");
                    return 1;
                }else{
                    fprintf(pacientesGeraisArq, "%d", i);
                    fclose(pacientesGeraisArq);
                }
            }

            fprintf(pacientesArq, "DADOS PESSOAIS:\n\n");
            fprintf(pacientesArq, "ID......................: %d", i);
            fprintf(pacientesArq, "\nNOME DO PACIENTE........: %s", paciente[i].nome);
            fprintf(pacientesArq, "\nCPF.....................: %s", paciente[i].cpf);
            fprintf(pacientesArq, "\nDATA DE NASCIMENTO......: %2.2d/%2.2d/%4.4d", paciente[i].dataNascimento.dia, paciente[i].dataNascimento.mes, paciente[i].dataNascimento.ano);
            fprintf(pacientesArq, "\nTELEFONE................: %s", paciente[i].telefone);
            fprintf(pacientesArq, "\nE-MAIL..................: %s", paciente[i].email);

            fprintf(pacientesArq,"\n\n-------------------------------------------------------------------------------------------------");

            fprintf(pacientesArq, "\n\nLOGRADOURO:\n");
            fprintf(pacientesArq, "\nRUA.....................: %s", paciente[i].endereco.rua);
            fprintf(pacientesArq, "\nNÚMERO..................: %s", paciente[i].endereco.numero);
            fprintf(pacientesArq, "\nBAIRRO..................: %s", paciente[i].endereco.bairro);
            fprintf(pacientesArq, "\nCIDADE..................: %s", paciente[i].endereco.cidade);
            fprintf(pacientesArq, "\nESTADO..................: %s", paciente[i].endereco.estado);
            fprintf(pacientesArq, "\nCEP.....................: %s", paciente[i].endereco.cep);

            fprintf(pacientesArq,"\n\n-------------------------------------------------------------------------------------------------");

            fprintf(pacientesArq, "\n\nDADOS DO DIAGNOSTICO DO PACIENTE:\n");
            fprintf(pacientesArq, "\nDATA DO DIAGNOSTICO.....: %2.2d/%2.2d/%4.4d", paciente[i].dataDiagnostico.dia, paciente[i].dataDiagnostico.mes, paciente[i].dataDiagnostico.ano);
            if(operacaoComorbidade == 1){
                fprintf(pacientesArq, "\nCOMORBIDADES DO PACIENTE: %s\n", paciente[i].comorbidadepaciente);
            }else{
                fprintf(pacientesArq, "\nCOMORBIDADES DO PACIENTE: O PACIENTE NÃO POSSUI COMORBIDADES.\n");
            }

            fprintf(pacientesArq, "\n_________________________________________________________________________________________________\n");
            fclose(pacientesArq);
            printf("\n\nCADASTRO >> SALVO << COM SUCESSO!!!\n");
            printf("\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU.\n");
            getch();
        }else{
            printf("\n\nCADASTRO >> CANCELADO <<\n");
            printf("\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU.\n");
            getch();
        }
    }
    ultimoIdGrupoRisco = 0;
    ultimoIdPacientesGerais = 0;
    i = 0;
    operacaoComorbidade = NULL;
    operacaoSalvarCadastro = NULL;
}

void painelExibirDados(){
    system("mode con:cols=100 lines=28");
    system("cls");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\tMENU INCIAL\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|_______________________________________________________________________________________________|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t1-PACIENTES GERAIS \t\t\t\t\t\t|\n");
    printf("|\t\t\t\t2-PACIENTES DO GRUPO DE RISCO\t\t\t\t\t|\n");
    printf("|\t\t\t\t3-VOLTAR AO MENU ANTERIOR\t\t\t\t\t|\n");
    printf("|_______________________________________________________________________________________________|\n\n\n");
    printf("DIGITE O NUMERO DA OPÇÃO QUE DESEJAR: ");
    operacaoExibirDados = validaNumerosCaracteres(operacaoExibirDados);
}
void exibirDados(){
    painelExibirDados();
    while (operacaoExibirDados != 0){
        switch(operacaoExibirDados){
            case 1:
                system("mode con:cols=100 lines=29");
                pacientesArq = fopen("pacientes fora do grupo de risco/pacientes_diagnosticados.txt", "r");
                pacientesGeraisArq = fopen("cache/contagem_pacientes_diagnosticados.txt", "r");
                fscanf(pacientesGeraisArq, "%d", &ultimoIdPacientesGerais);
                fclose(pacientesGeraisArq);

                if(pacientesArq == NULL && operacaoExibirDados == 1 || ultimoIdPacientesGerais == NULL && operacaoExibirDados == 1){
                    system("cls");
                    printf("NÃO EXISTE PACIENTES CADASTRADOS.\n\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                    break;
                }
                system("cls");
                while(!feof(pacientesArq) && linhas <= limiteLinhas){
                    fgets(texto, 1000, pacientesArq);
                    if(strlen(texto) < 1000){
                        linhas++;
                        printf("%s", texto);
                        if(linhas == limiteLinhas){
                            limiteLinhas += 28;
                            printf("DIGITE > 1 < PARA OLHAR A PROXIMA PAGINA OU > 2 < PARA RETORNAR: ");
                            operacaoProximoPaciente = validaNumerosCaracteres(operacaoProximoPaciente);
                            while(operacaoProximoPaciente != 1 && operacaoProximoPaciente != 2){
                                system("cls");
                                printf("OPÇÃO INVALIDA!\n\n");
                                printf("DIGITE > 1 < PARA OLHAR A PROXIMA PAGINA OU > 2 < PARA RETORNAR: ");
                                operacaoProximoPaciente = validaNumerosCaracteres(operacaoProximoPaciente);
                            }
                            if(operacaoProximoPaciente == 2){
                                break;
                            }
                        }
                    }
                }
                if(operacaoProximoPaciente == 1){
                    system("cls");
                    printf("NÃO HÁ MAIS CADASTROS SALVOS.\n\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }
                break;
            case 2:
                system("mode con:cols=100 lines=29");
                pacientesArq = fopen("pacientes do grupo de risco/grupo_de_risco.txt", "r");
                grupoRiscoArq = fopen("cache/contagem_grupo_de_risco.txt", "r");
                fscanf(grupoRiscoArq, "%d", &ultimoIdPacientesGerais);
                fclose(grupoRiscoArq);

                if(pacientesArq == NULL && operacaoExibirDados == 2 || ultimoIdPacientesGerais == NULL && operacaoExibirDados == 2){
                    system("cls");
                    printf("NÃO EXISTE PACIENTES DO GRUPO DE RISCO CADASTRADOS.\n\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                    break;
                }
                system("cls");
                while(!feof(pacientesArq) && linhas <= limiteLinhas){
                    fgets(texto, 1000, pacientesArq);
                    if(strlen(texto) < 1000){
                        linhas++;
                        printf("%s", texto);
                        if(linhas == limiteLinhas){
                            limiteLinhas += 28;
                            printf("DIGITE > 1 < PARA OLHAR A PROXIMA PAGINA OU > 2 < PARA RETORNAR: ");
                            operacaoProximoPaciente = validaNumerosCaracteres(operacaoProximoPaciente);
                            while(operacaoProximoPaciente != 1 && operacaoProximoPaciente != 2){
                                system("cls");
                                printf("OPÇÃO INVALIDA!\n\n");
                                printf("DIGITE > 1 < PARA OLHAR A PROXIMA PAGINA OU > 2 < PARA RETORNAR: ");
                                operacaoProximoPaciente = validaNumerosCaracteres(operacaoProximoPaciente);
                            }
                            if(operacaoProximoPaciente == 2){
                                break;
                            }
                        }
                    }
                }
                if(operacaoProximoPaciente == 1){
                    system("cls");
                    printf("NÃO HÁ MAIS CADASTROS SALVOS NO GRUPO DE RISCO.\n\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }
                break;
            case 3:
                return;
            case 0:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
            default:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
        }
        linhas = 0;
        limiteLinhas = 28;
        fclose(pacientesArq);
        painelExibirDados();
    }
    operacaoMenuInicial = 5;
}

void painelExcluirDados(){
    system("mode con:cols=100 lines=28");
    system("cls");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\tMENU INCIAL\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|_______________________________________________________________________________________________|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t1-EXCLUIR TODOS OS DADOS DOS PACIENTES GERAIS\t\t\t|\n");
    printf("|\t\t\t\t2-EXCLUIR TODOS OS DADOS DO GRUPO DE RISCO\t\t\t|\n");
    printf("|\t\t\t\t3-VOLTAR AO MENU ANTERIOR\t\t\t\t\t|\n");
    printf("|_______________________________________________________________________________________________|\n\n\n");
    printf("DIGITE O NUMERO DA OPÇÃO QUE DESEJAR: ");
    operacaoExcluirDados = validaNumerosCaracteres(operacaoExcluirDados);
}
void excluirDados(){
    painelExcluirDados();
    while(operacaoExcluirDados != 0){
        switch(operacaoExcluirDados){
            case 1:
                printf("\n\nDESEJA REALMENTE APAGAR TODOS OS DADOS DOS > PACIENTES GERAIS <?\nDIGITE > 1 < PARA APAGAR OU > 2 < PARA CANCELAR: ");
                operacaoConfirmarExcluir = validaNumerosCaracteres(operacaoConfirmarExcluir);

                if(operacaoConfirmarExcluir != 1 && operacaoConfirmarExcluir != 2){
                    printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                    break;
                }

                if(operacaoConfirmarExcluir == 1){
                    pacientesGeraisArq = fopen("cache/contagem_pacientes_diagnosticados.txt", "w");
                    fclose(pacientesGeraisArq);
                    remove("cache/contagem_pacientes_diagnosticados.txt");

                    pacientesArq = fopen("pacientes fora do grupo de risco/pacientes_diagnosticados.txt", "w");
                    fclose(pacientesArq);
                    remove("pacientes fora do grupo de risco/pacientes_diagnosticados.txt");

                    printf("\n\nDADOS DE PACIENTES GERAIS APAGADOS COM SUCESSO!\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }else{
                    printf("\nOPERAÇÃO CANCELADA\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }
                break;
            case 2:
                printf("\n\nDESEJA REALMENTE APAGAR TODOS OS DADOS DO > GRUPO DE RISCO <?\nDIGITE > 1 < PARA APAGAR OU > 2 < PARA CANCELAR: ");
                fflush(stdin);
                operacaoConfirmarExcluir = validaNumerosCaracteres(operacaoConfirmarExcluir);

                if(operacaoConfirmarExcluir != 1 && operacaoConfirmarExcluir != 2){
                    printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                    break;
                }
                if(operacaoConfirmarExcluir == 1){
                    grupoRiscoArq = fopen("cache/contagem_grupo_de_risco.txt", "w");
                    fclose(grupoRiscoArq);
                    remove("cache/contagem_grupo_de_risco.txt");

                    pacientesArq = fopen("pacientes do grupo de risco/grupo_de_risco.txt", "w");
                    fclose(pacientesArq);
                    remove("pacientes do grupo de risco/grupo_de_risco.txt");

                    printf("\n\nDADOS DE GRUPO DE RISCO APAGADOS COM SUCESSO!\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }else{
                    printf("\nOPERAÇÃO CANCELADA\n");
                    printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                    getch();
                }
                break;
            case 3:
                return;
            case 0:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
            default:
                printf("\n\nOPÇÃO INVÁLIDA!\n\n");
                printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
                getch();
                break;
        }
        operacaoConfirmarExcluir = NULL;
        operacaoExcluirDados = NULL;
        painelExcluirDados();
    }
    operacaoMenuInicial = 5;
}

void painelInformacoesSistemas(){
        system("mode con:cols=100 lines=28");
        system("cls");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tINFORMAÇÕES DO SISTEMA\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|_______________________________________________________________________________________________|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tDESENVOLVIDO POR:\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tMATHEUS DOS SANTOS BATISTA\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\tCOPYRIGHT©2022\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t\t\t\t\t\t\t\t\t|\n");
        printf("|\t\t\t\t3-VOLTAR AO MENU ANTERIOR\t\t\t\t\t|\n");
        printf("|_______________________________________________________________________________________________|\n\n\n");
        printf("DIGITE O NUMERO DA OPÇÃO QUE DESEJAR: ");
        operacaoInformacoesSistemas = validaNumerosCaracteres(operacaoInformacoesSistemas);
}
void informacoesSistemas(){
    painelInformacoesSistemas();

    while(operacaoInformacoesSistemas != 0){
        switch(operacaoInformacoesSistemas){
        case 3:
            return;
        case 0:
            printf("\n\nOPÇÃO INVÁLIDA!\n\n");
            printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
            getch();
            break;
        default:
            printf("\n\nOPÇÃO INVÁLIDA!\n\n");
            printf("\nPRESSIONE QUALQUER TECLA PARA SEGUIR!");
            getch();
            break;
        }
        operacaoInformacoesSistemas = NULL;
        painelInformacoesSistemas();
    }
    operacaoMenuInicial = 5;
}

int bissexto(ano){
    if(ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0){
        return 1;
    }else{
        return 0;
    }
}
int validarData(int dia,int mes,int ano){
    int contaDigitosDia = 0, contaDigitosMes = 0, contaDigitosAno = 0, valorDia, valorMes, valorAno, anoAtual;
    time(&segundos);
    dataAtual = localtime(&segundos);
    anoAtual = dataAtual->tm_year + 1900;
    valorDia = dia;
    valorMes = mes;
    valorAno = ano;
    do{
        if(valorDia != 0){
            contaDigitosDia++;
            valorDia = valorDia / 10;
        }
        if(valorMes != 0){
            contaDigitosMes++;
            valorMes = valorMes / 10;
        }
        if(valorAno != 0){
            contaDigitosAno++;
            valorAno = valorAno / 10;
        }
    }while(valorDia != 0 || valorMes != 0 || valorAno != 0);

    if(dia < 1 || dia > 31 || mes < 1 || mes > 12){
        return 0;
    }
    if(dia == 31 && (mes == 4 || mes == 6 || mes == 9 || mes == 11)){
        return 0;
    }
    if(mes == 2 && dia > 29){
        return 0;
    }
    if(ano < 1900 || ano > anoAtual){
        return 0;
    }
    if(mes == 2 && dia == 29 && bissexto(ano) == 0){
        return 0;
    }
    if(contaDigitosDia > 2){
        return 0;
    }
    if(contaDigitosMes > 2){
        return 0;
    }
    if(contaDigitosAno != 2 && contaDigitosAno != 4){
        return 0;
    }
    return 1;
}
int diasNoMes(mes, ano){
    if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
       return 31;
    }else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        return 30;
    }else if(bissexto(ano) == 1){
        return 29;
    }else{
        return 28;
    }

}
int calcularIdade(diaNascimento, mesNascimento, anoNascimento){
    int diaAtual, mesAtual, anoAtual, qtdDias = 0,qtdMeses = 0, qtdAnos = 0;

    time(&segundos);
    dataAtual = localtime(&segundos);

    diaAtual = dataAtual->tm_mday;
    mesAtual = dataAtual->tm_mon+1;
    anoAtual = dataAtual->tm_year+1900;

    while(mesNascimento < mesAtual - 1 || anoNascimento < anoAtual){
        mesNascimento++;
        qtdMeses++;
        if(qtdMeses == 12){
            qtdMeses = 0;
            qtdAnos++;
        }
        if(mesNascimento > 12){
            anoNascimento++;
            mesNascimento = 0;
        }
    }
    if(diaNascimento == diaAtual){
       qtdMeses++;
       qtdDias = 0;
       }else if(diaNascimento < diaAtual){
        qtdMeses++;
        qtdDias = diaAtual - diaNascimento;
       }else{
           qtdDias = diasNoMes(mesAtual - 1, anoAtual) + diaAtual - diaNascimento;
       }
        qtdDiasIdade = qtdDias;
        qtdMesesIdade = qtdMeses;
        qtdAnosIdade = qtdAnos;
}

int validarEmail(char email[]){

    int b, a = 0, contador = 0, contadorPonto = 0, tam = strlen(email);
    if(tam >= 50 || tam <= 2){
        return 0;
    }else{
        for(b = 0; b < tam; b++){

            if (email[b] == '@'){
                contador++;
                b+=3;
            }
            if (contador == 1){
              if (email[b] == '.'){
                contadorPonto++;
                }
            }
        }
        if(contador == 1 && contadorPonto >= 1){
            return 1;
        }else {
            return 0;
        }
    }
}

void validaApenasLetras(char letras[50]){
    o = 0;
    do{
        t=getch();
        if(t==27){
            printf("\n\n");
            return;
        }
        if (isalpha(t)!= 0 || t==32){
            letras[o] = toupper(t);
            o++;
            printf("%c", toupper(t));
        }else if(t == 8 && o){
            letras[o] = '\0';
            o--;
            printf("\b \b");
        }
    }while(t != 13);

    letras[o]='\0';

    printf("\n");
}
void validaApenasNumeros(char numeroDigitado[50]){
    o = 0;
    numeros = 0;
    do{
        t=getch();
        if(t==27){
            printf("\n\n");
            return;
        }
        if (isdigit(t)!= 0){
            numeroDigitado[o] = t;
            o++;
            printf("%c", t);
        }else if(t == 8 && o){
            numeroDigitado[o] = '\0';
            o--;
            printf("\b \b");
        }
    }while(t != 13);

    numeroDigitado[o]='\0';
    numeros = atoi(numeroDigitado);
    printf("\n");
}

void validaCaractere(char caractere[200]){
    o = 0;
    do{
        t=getch();
        if(t==27){
            printf("\n\n");
            return;
        }
        if (t != 8){
            caractere[o] = toupper(t);
            o++;
            printf("%c", toupper(t));
        }else if(t == 8 && o){
            caractere[o] = '\0';
            o--;
            printf("\b \b");
        }
    }while(t != 13);

    caractere[o]='\0';

    printf("\n");
}
int validaNumerosCaracteres(int numero){
    numeroChar[200] = numero;
    o = 0;
    do{
        t=getch();
        if(t==27){
            printf("\n\n");
            return;
        }
        if (isdigit(t)!= 0){
            numeroChar[o] = t;
            o++;
            printf("%c", t);
        }else if(t == 8 && o){
            numeroChar[o] = '\0';
            o--;
            printf("\b \b");
        }
    }while(t != 13);

    numeroChar[o]='\0';
    numero = atoi(numeroChar);
    printf("\n");


    return numero;
}
