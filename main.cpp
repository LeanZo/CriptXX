#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>


using namespace std;

static string cifraVigenere[26][26];

static void gerarCifra(string (&cifraVigenere)[26][26])
{
    int i3 = 0;

    vector<string> letrasBasicas { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

    for (int i = 0; i <= 25; i++)
    {

        for (int i2 = 0; i2 <= 25; i2++)
        {
            if (i == 0)
            {
                cifraVigenere[i2][i] = letrasBasicas[i2];
            } else
            {
                if ((i2 + i) > 25)
                {
                    cifraVigenere[i2][i] = letrasBasicas[i3];
                    i3++;
                } else {
                cifraVigenere[i2][i] = letrasBasicas[i2 + i];
                }

            }
        }
        i3 = 0;
    }
}

static void encriptar(vector<char> (&fileLines), string (&cifraVigenere)[26][26], string palavraChave)
{
    vector<char> letrasBasicas { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    int colunaID = 666;
    int linhaID = 666;
    string fraseEncriptada = "";
    int palavraChaveIndex = 0;
    int fileLinesEncriptadoIndex = 0;
    int fileLinesSize = fileLines.size();
    string selecionada = "";
    vector<char> fileLinesEncriptado;

    for(auto letra : fileLines)
    {
        for(auto alfabeto : letrasBasicas)
        {
            if (std::toupper(letra) == alfabeto)
            {
                for (int i = 0; i < letrasBasicas.size(); i++)
                {
                     if (std::toupper(letra) == letrasBasicas[i])
                     {
                        colunaID = i;
                        break;
                     }
                }
                if (palavraChaveIndex < palavraChave.length())
                {
                    for (int i = 0; i < letrasBasicas.size(); i++)
                    {
                        if (palavraChave[palavraChaveIndex] == letrasBasicas[i])
                         {
                            linhaID = i;
                            break;
                         }
                    }
                    palavraChaveIndex++;
                } else
                {
                    palavraChaveIndex = 0;

                    for (int i = 0; i < letrasBasicas.size(); i++)
                    {
                         if (palavraChave[palavraChaveIndex] == letrasBasicas[i])
                         {
                             linhaID = i;
                             break;
                         }
                    }
                    palavraChaveIndex++;
                }
                break;
            }
        }
        if (colunaID != 666)
        {
            if (std::isupper(letra))
            {
                stringstream ss;
                ss << cifraVigenere[linhaID][colunaID];
                ss >> fraseEncriptada;
                //std::copy(fraseEncriptada.begin(), fraseEncriptada.end(), std::back_inserter(fileLinesEncriptado));
            } else
            {
                string letraLower = cifraVigenere[linhaID][colunaID];
                std::transform(letraLower.begin(), letraLower.end(), letraLower.begin(), ::tolower);
                fraseEncriptada.append(letraLower);
                //std::copy(letraLower.begin(), letraLower.end(), std::back_inserter(fileLinesEncriptado));
            }
            colunaID = 666;
        } else
        {
            /*stringstream ss;
            ss << letra;
            ss >> fraseEncriptada;*/
            fileLinesEncriptado.push_back(letra);

        }
        std::copy(fraseEncriptada.begin(), fraseEncriptada.end(), std::back_inserter(fileLinesEncriptado));
        fraseEncriptada = "";
        fileLinesEncriptadoIndex++;
    }


    fileLines = vector<char>();

    fileLines = fileLinesEncriptado;
}

static void decriptar(vector<char> (&fileLines), string (&cifraVigenere)[26][26], string palavraChave)
{
    vector<string> letrasBasicas { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    int colunaID = 666;
    int linhaID = 666;
    string fraseDecriptada = "";
    int palavraChaveIndex = 0;
    int fileLinesDecriptadoIndex = 0;
    vector<char>fileLinesDecriptado;
    bool isLetra = false;

    for(auto letra : fileLines)
    {
        isLetra = false;
        for(string alfabeto : letrasBasicas)
        {
            if (std::toupper(letra) == alfabeto.c_str()[0])
            {
                isLetra = true;
                break;
            }
        }

        if (isLetra)
        {
            if (palavraChaveIndex < palavraChave.length())
            {
                for(int i = 0; i < letrasBasicas.size(); i++)
                {
                    string letrasBasicasString = string(letrasBasicas[i]);
                    if(letrasBasicasString.c_str()[0] == palavraChave[palavraChaveIndex])
                    {
                        linhaID = i;
                    }
                }

            palavraChaveIndex++;

            }
            else
            {
                palavraChaveIndex = 0;

                for(int i = 0; i < letrasBasicas.size(); i++)
                {
                    string letrasBasicasString = string(letrasBasicas[i]);
                    if(letrasBasicasString.c_str()[0] == palavraChave[palavraChaveIndex])
                    {
                        linhaID = i;
                    }
                }

                palavraChaveIndex++;
            }

            for (int i = 0; i <= 25; i++)
            {
                string letraString(1, std::toupper(letra));
                if (letraString == cifraVigenere[linhaID][i])
                {
                    colunaID = i;
                    break;
                }

            }

            if (std::isupper(letra))
            {
                stringstream ss;
                ss << letrasBasicas[colunaID];
                ss >> fraseDecriptada;
            } else
            {
                stringstream ss;
                string letraLower = letrasBasicas[colunaID];
                std::transform(letraLower.begin(), letraLower.end(), letraLower.begin(), ::tolower);
                fraseDecriptada.append(letraLower);
            }
        }
        else
        {
            /*stringstream ss;
            ss << letra;
            ss >> fraseDecriptada;*/
			fraseDecriptada.push_back(letra);
        }

        std::copy(fraseDecriptada.begin(), fraseDecriptada.end(), std::back_inserter(fileLinesDecriptado));
        fraseDecriptada = "";
        fileLinesDecriptadoIndex++;
    }

    fileLines = vector<char>();

    fileLines = fileLinesDecriptado;
}

static std::vector<char> ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

int main(int argc, char *argv[])
{
    gerarCifra(cifraVigenere);

    cout << "Select the desired option:" << endl << "1 - Encrypt" << endl << "2 - Decrypt"
         << endl << "> ";

    string option;
    getline(cin, option);

    cout << endl << "Insert file name: ";
    string filename;
    getline(cin, filename);

    std::vector<char> fileLines = ReadAllBytes(filename.c_str());

    cout << "Insert KEY: ";
    string key;
    getline(cin, key);
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);

    if(option == "1")
    {
        encriptar(fileLines, cifraVigenere, key);
    } else {
        decriptar(fileLines, cifraVigenere, key);
    }

    std::ofstream file;
    file.open(filename + " XX");

    for(int i = 0; i < fileLines.size(); i++)
    {
        cout << fileLines[i];
        file << fileLines[i];
    }
    cout << endl;

    return 0;
}
