#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <iomanip>

using namespace std;

int ventas = 0;

class Persona {
private:
    string email;
    string clave;
    
public:
    int dni;
    int codigo;
    string nombre;
    int telefono;

    Persona() {}
    Persona(string email, string clave, string nombre,int dni, int telefono) {
        this->email = email;
        this->clave = clave;
        this->nombre = nombre;
        this->dni = dni;
        this->telefono = telefono;
    }
};

class Producto {
public:
    int codigo;
    string descripcion;
    double precio;
    string tipo;
    int stock;
    int capacidad;
    static int numeroProductos;

    Producto() {}
    Producto(string descripcion, double precio, string tipo, int stock, int capacidad) {
        numeroProductos +=1;
        this->descripcion = descripcion;
        this->precio = precio;
        this->tipo = tipo;
        this->stock = stock;
        this->capacidad = capacidad;
        codigo = 3000 + numeroProductos;
    }
};

int Producto::numeroProductos = 0;


class Cliente : public Persona {
protected:
    double tasaDescuento;
    vector <Producto*> productos;

public:
    static int numeroClientes;
    char categoria;
    string ruc;
    string direccion;

    Cliente() {}
    Cliente(string email, string clave, string nombre, int dni, int telefono, string ruc, string direccion) : Persona(email, clave, nombre, dni, telefono) {
        this->categoria = 'C';
        this->ruc = ruc;
        this->direccion = direccion;
        numeroClientes += 1;
        codigo = 1000 + numeroClientes;
    }

    friend ostream& operator<<(ostream& o, const Cliente& cliente) {
        o << "Cliente: " << cliente.codigo  << " " << cliente.nombre << " " << cliente.telefono << " " << cliente.categoria << " " << cliente.ruc << " " << cliente.direccion << endl;
        return o;
    }

    Cliente& agregarCompra(Producto* x) {
        productos.push_back(x);
        return *this;
    }
    virtual void asignarCategoria() = 0;

    vector<Producto*> getCompras() {
        return productos;
    }
};

int Cliente::numeroClientes = 0;

class ClienteIndividual : public Cliente {
public:
    ClienteIndividual() {}
    ClienteIndividual(string email, string clave, string nombre,int dni, int telefono, string ruc, string direccion) : Cliente(email, clave, nombre,dni, telefono, ruc, direccion) {
        this->tasaDescuento = 0.03;
    }

    void asignarCategoria() {
        cout << "Ingrese la categoria: ";
        while(categoria != 'A' or categoria !='B' or categoria != 'D' ){
            cin >> categoria;
        }
        
    }
};

class ClienteCorporativo : public Cliente {
public:
    ClienteCorporativo() {}
    ClienteCorporativo(string email, string clave, string nombre,int dni, int telefono, string ruc, string direccion) : Cliente(email, clave, nombre, dni,telefono, ruc, direccion) {
        this->tasaDescuento = 0.10;
    }

    void asignarCategoria() {
        cout << "Ingrese la categoria: ";
        while(categoria != 'A' or categoria !='B' ){
            cout << "Cliente Corporativo solo puede ser categoria A o B" << endl;
            cin >> categoria;
        }
    }
};

class Vendedor : public Persona {
private:
    static int numeroVendedores;

public:
    double salario;

    Vendedor(string nombre, double salario) {
        this->nombre = nombre;
        this->salario = salario;
        numeroVendedores += 1;
        codigo = 2000 + numeroVendedores;
    }
};

int Vendedor::numeroVendedores = 0;


void limpiarPantalla() {
    system("cls");
}

int obtenerOpcion() {
    int opcion;
    bool opcionValida = false;

    while (!opcionValida) {
        if (cin >> opcion) {
            opcionValida = true;
        } else {
            cout << "Opción inválida. Intente nuevamente: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[2J\033[1;1H";
        }
    }

    return opcion;
}

void agregarNuevoCliente(vector<Cliente*>& clientes) {
    Cliente* c;
    char opc;
    string email;
    string clave;
    int codigo;
    string nombre;
    int telefono;
    string ruc;
    string direccion;
    int dni;

    if (Cliente::numeroClientes < 6)
    {
        cout << "Elija el tipo de cliente" << endl;
            cout << "1. Cliente Corporativo" << endl;
            cout << "2. Cliente Individual" << endl;
            cout << "Elija una opcion: ";
            cin >> opc;

            switch (opc) {
                case '1': {
                    cout << "Ingrese los datos del cliente corporativo" << endl;
                    cout << "Email: ";
                    cin >> email;
                    cout << "Clave: ";
                    cin >> clave;
                    cout << "Nombre: ";
                    cin >> nombre;
                    cout << "Dni: ";
                    cin >> dni;
                    cout << "Telefono: ";
                    cin >> telefono;
                    cout << "Ruc: ";
                    cin >> ruc;
                    cout << "Direccion: ";
                    cin.ignore();
                    getline(cin, direccion);

                    // Validar si el cliente ya está registrado por DNI y Nombre
                    for (auto& it : clientes) {
                        if (it->nombre == nombre and it->dni == dni) {
                            cout << "El cliente ya existe en la base de datos";
                            return;
                        }
                    }

                    // Validar tamaño del RUC (11 dígitos)
                    while (ruc.length() != 11) {
                        cout << "El RUC debe tener 11 dígitos. Ingrese nuevamente: ";
                        cin >> ruc;
                    }

                    // Validar tamaño del teléfono (9 dígitos)
                    while (telefono < 100000000 or telefono > 999999999) {
                        cout << "El teléfono debe tener 9 dígitos. Ingrese nuevamente: ";
                        cin >> telefono;
                    }

                    if (Cliente::numeroClientes >= 6) {
                        cout << "Agenda llena. No se puede agregar más clientes." << endl;
                        break;
                    }
                    
                    c = new ClienteCorporativo(email, clave, nombre,dni, telefono, ruc, direccion);
                    clientes.push_back(c);
                    break;
                }

                case '2': {
                    cout << "Ingrese los datos del cliente individual" << endl;
                    cout << "Email: ";
                    cin >> email;
                    cout << "Clave: ";
                    cin >> clave;
                    cout << "Nombre: ";
                    cin >> nombre;
                    cout << "Telefono: ";
                    cin >> telefono;
                    cout << "Ruc: ";
                    cin >> ruc;
                    cout << "Direccion: ";
                    cin.ignore();
                    getline(cin, direccion);


                    // Validar si el cliente ya está registrado por DNI y Nombre
                    for (auto& it : clientes) {
                        if (it->nombre == nombre and it->dni == dni) {
                            cout << "El cliente ya existe en la base de datos";
                            return;
                        }
                    }

                    // Validar tamaño del RUC (11 dígitos)
                    while (ruc.length() != 11) {
                        cout << "El RUC debe tener 11 dígitos. Ingrese nuevamente: ";
                        cin >> ruc;
                    }

                    // Validar tamaño del teléfono (9 dígitos)
                    while (telefono < 100000000 or telefono > 999999999) {
                        cout << "El teléfono debe tener 9 dígitos. Ingrese nuevamente: ";
                        cin >> telefono;
                    }

                    c = new ClienteIndividual(email, clave, nombre, dni,telefono, ruc, direccion);
                    clientes.push_back(c);
                    
                    break;
                }

                default: {
                    cout << "Ingresó una opción incorrecta" << endl;
                    break;
                }
            }
    }

    else 
        cout << "Agenda llena" << endl;
    
}

void buscarCliente(vector<Cliente*>& clientes) {
    int codigo;
    cout << "Ingrese el código del cliente: ";
    cin >> codigo;

    bool clienteExistente = false;
    for (auto& cliente : clientes) {
        if (cliente->codigo == codigo) {
            clienteExistente = true;
            cout << "El cliente sí existe:" << endl;
            cout << "Código: " << cliente->codigo << endl;
            cout << "Nombre: " << cliente->nombre << endl;
            // Imprime los demás atributos que desees mostrar
            break;
        }
    }

    if (!clienteExistente) {
        cout << "El cliente no existe en la lista." << endl;
    }
}

void agregarNuevoVendedor(vector<Vendedor>& vendedores) {
    string nombre;
    cout << "Ingrese el nombre del vendedor: ";
    cin >> nombre;

    bool vendedorExistente = false;
    for (auto& vendedor : vendedores) {
        if (vendedor.nombre == nombre) {
            vendedorExistente = true;
            break;
        }
    }

    if (vendedorExistente) {
        cout << "Error, vendedor ya registrado" << endl;

    } else {
        int codigo;
        double salario;
        cout << "Ingrese el salario del vendedor: ";
        cin >> salario;
        Vendedor nuevoVendedor(nombre, salario);
        vendedores.push_back(nuevoVendedor);
        cout << "Se agregó el nuevo vendedor: " << nuevoVendedor.nombre << endl;
    }
}

void agregarNuevoProducto(vector<Producto>& productos) {
    int codigo;
    string descripcion;
    double precio;
    string tipo;
    int stock;
    int capacidad;

    cout << "Ingrese la descripción del producto: ";
    cin.ignore();
    getline(cin, descripcion);
    cout << "Ingrese el precio del producto: ";
    cin >> precio;
    cout << "Ingrese el tipo del producto: ";
    cin.ignore();
    getline(cin, tipo);
    cout << "Ingrese el stock del producto: ";
    cin >> stock;
    cout << "Ingrese la capacidad del producto: ";
    cin >> capacidad;

    Producto nuevoProducto(descripcion, precio, tipo, stock, capacidad);
    productos.push_back(nuevoProducto);
    cout << "Se agregó el nuevo producto." << endl;
}
int cont = 0 ;

void realizarVenta(vector<Cliente*>& clientes, vector<Producto>& productos) {
    int codigoCliente, cantidad;
    double total = 0;
    char confirmar;
    cout << "Ingrese el código del cliente: ";
    cin >> codigoCliente;

    bool clienteExistente = false;
    Cliente* cliente;
    for (auto& c : clientes) {
        if (c->codigo == codigoCliente) {
            clienteExistente = true;
            cliente = c;
            break;
        }
    }

    if (!clienteExistente) {
        cout << "El cliente no existe en la lista." << endl;
        return;
    }

    int codigoProducto;
    cout << "Ingrese el código del producto: ";
    cin >> codigoProducto;

    bool productoExistente = false;
    Producto* producto;
    for (auto& p : productos) {
        if (p.codigo == codigoProducto) {
            productoExistente = true;
            producto = &p;
            break;
        }
    }

    if (!productoExistente) {
        cout << "El producto no existe en la lista." << endl;
        return;
    }

    cout << "Ingrese la cantidad que desea comprar: ";
    cin >> cantidad;

    if (cantidad <= producto->stock) {
        cout << "Desea confirmar la compra S/N: ";
        cin >> confirmar;
    }

    else {
        cout << "No contamos con stock suficiente para su compra :(" << endl;
        cout << "Stock Disponible: " << producto->stock << endl;
        return;
    }


        if(confirmar == 'S' || confirmar == 's') {
            ventas += 1;
            time_t t = time(NULL);
            cout << "Realizando venta..." << endl;
            cliente->agregarCompra(producto);

            cout << "\n                                          Venta "<< ventas << endl ;
            cout << "FECHA Y HORA: " << ctime(&t) << endl;

            cout << left << setw(20) << "COD"
                << setw(30) << "PRODUCTO"
                << setw(20) << "CANTIDAD"
                << setw(20) << "PRECIO UNI."
                << setw(20) << "SUBTOTAL" << endl;

            for(auto& p : cliente->getCompras()) {
                double subtotal = p->precio * cantidad;
                cout << left << setw(20) << p->codigo
                    << setw(30) << p->descripcion
                    << setw(20) << cantidad
                    << setw(20) << p->precio
                    << subtotal << endl;
                total += subtotal;
            }
        


        cout << "\nTOTAL " << total << " SOLES" << endl;

        ofstream archivo("venta.txt");
        if (archivo.is_open())
        {
            archivo<<"Venta"<<cont<<endl;
            archivo<<"Cliente"<<cliente->nombre<<endl;
            archivo<<"Fecha 28/06/2023"<<endl;
            archivo<<"Cod"<<codigoProducto<<endl;
            archivo<<"Producto"<<producto->descripcion<<endl;
            archivo.close();
        }
        else
        {
            cout<<"No se pudo abrir el archivo"<<endl;
        }
    }

    else 
        cout << "La compra no ha sido procesada"<< endl;
    
}
bool compararClientes(const Cliente* x1, const Cliente* x2) {
    return x1->codigo < x2->codigo;
}

vector <Cliente*> ordenarClientes(vector <Cliente*> x) {
    sort(x.begin(), x.end(), compararClientes);
    return x;
}

void mostrarClientes(vector <Cliente*>& x) {
    cout << "+------------------+" << "--------------------+" << "-----------------+" << "-----------------------+" << endl; 
    cout << "|      Codigo      |" << "      Telefono      |" << "    Categoria    |" << "          RUC          |" << endl;
    cout << "+------------------+" << "--------------------+" << "-----------------+" << "-----------------------+"  << endl; 
    x = ordenarClientes(x);
    for(auto i : x) {
        
        cout <<"|       "<< i->codigo  <<"       |"<< "     "<< i->telefono  <<"      |" <<"        "<< i->categoria  <<"        |" <<"      "<<i->ruc<< "      |"<< endl;
        cout << "+------------------+" << "--------------------+" << "-----------------+"  << "-----------------------+"  <<endl; 
    }
}

template <typename T> 
bool compararPorCodigo(const T& x1, const T& x2) {
    return x1.codigo < x2.codigo;
}

template <typename T> 
void ordenarListaAscendente(vector <T> x) {
    sort(x.begin(), x.end(), compararPorCodigo);
}

template <typename T> 
vector <T> ordenarListaDescendente(vector <T> x) {
    sort(x.rbegin(), x.rend() , compararPorCodigo<T>);
    return x;
}


void mostrarProductos(vector<Producto>& productos) {
    cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;
    cout << "|   Codigo     |" << "        Descripcion         |" << "         Precio      |" << endl;
    cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;
    productos = ordenarListaDescendente<Producto>(productos);
    for(const auto& producto : productos) {
        cout << "| " << setw(12) << left << producto.codigo << " |" 
             << setw(27) << left << producto.descripcion << " |" 
             << setw(19) << left << producto.precio << " |" << endl;
        cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;
    }
}

void mostrarVendedores(const vector<Vendedor>& vendedores) {
    cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;
    cout << "|   Codigo     |" << "          Nombre            |" << "       Salario       |" << endl;
    cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;

    for (const auto& vendedor : vendedores) {
        cout << "| " << setw(12) << right << vendedor.codigo << " |" 
             << setw(27) << left << vendedor.nombre << " |" 
             << setw(19) << right << vendedor.salario << " |" << endl;
        cout << "+--------------+" << "----------------------------+" << "---------------------+" << endl;
    }
}




int main() {
    vector<Cliente*> clientes;
    vector<Vendedor> vendedores;
    vector<Producto> productos;

    Cliente* c1 = new ClienteIndividual("cliente1@example.com", "clave1", "Cliente 1",72685492, 123456789, "12345678921", "Dirección 1");
    Cliente* c2 = new ClienteCorporativo("cliente2@example.com", "clave2", "Cliente 2",72685493, 987654321,"54321678912", "Dirección 2");
    Cliente* c3 = new ClienteIndividual("cliente3@example.com", "clave3", "Cliente 3", 72685494, 938483007, "12345567892", "Dirección 3");

    Producto producto1("Martillo", 10.99, "Ferreteria", 50, 0);
    Producto producto2("Destornillador", 5.99, "Ferreteria", 100, 0);
    Producto producto3("Taladro", 59.99, "Ferreteria", 20, 0);

    clientes.push_back(c3);
    clientes.push_back(c1);
    clientes.push_back(c2);

    productos.push_back(producto1);
    productos.push_back(producto2);
    productos.push_back(producto3);

    int opcion;
    do {
        cout << "---------- SISTEMA COMERCIAL ----------\n" << endl;
        cout << "1. NUEVOS CLIENTES" << endl;
        cout << "2. BUSCAR CLIENTES" << endl;
        cout << "3. NUEVO VENDEDOR" << endl;
        cout << "4. NUEVO PRODUCTO" << endl;
        cout << "5. VENTAS" << endl;
        cout << "6. LISTA DE CLIENTES" << endl;
        cout << "7. LISTA DE VENDEDORES" << endl;
        cout << "8. LISTA DE PRODUCTOS" << endl;
        cout << "9. SALIR\n" << endl;
        cout << "Ingrese la opción a realizar: ";
        opcion = obtenerOpcion();

        switch (opcion) {
        case 1:
            agregarNuevoCliente(clientes);
            break;
        case 2:
            buscarCliente(clientes);
            break;
        case 3:
            agregarNuevoVendedor(vendedores);
            break;
        case 4:
            agregarNuevoProducto(productos);
            break;
        case 5:
            realizarVenta(clientes, productos);
            break;
        case 6:
            mostrarClientes(clientes);
            break;
        case 7:
            mostrarVendedores(vendedores);
            break;
        case 8:
            mostrarProductos(productos);
        case 9:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
    } while (opcion != 9);

    return 0;
}
