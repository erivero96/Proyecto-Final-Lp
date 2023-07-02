#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Persona {
private:
    string email;
    string clave;

public:
    int codigo;
    string nombre;
    int telefono;

    Persona() {}
    Persona(string email, string clave, string nombre, int telefono) {
        this->email = email;
        this->clave = clave;
        this->nombre = nombre;
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
    Producto(int codigo, string descripcion, double precio, string tipo, int stock, int capacidad) {
        this->codigo = codigo;
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
    vector <Producto> productos;

public:

    static int numeroClientes;
    char categoria;
    string ruc;
    string direccion;

    Cliente() {}
    Cliente(string email, string clave, string nombre, int telefono, string ruc, string direccion) : Persona(email, clave, nombre, telefono) {
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

    Cliente& agregarCompra(Producto& x) {
        productos.push_back(x);
        return *this;
    }
    virtual void asignarCategoria() = 0;
};

int Cliente::numeroClientes = 0;

class ClienteIndividual : public Cliente {
public:
    ClienteIndividual() {}
    ClienteIndividual(string email, string clave, string nombre, int telefono, string ruc, string direccion) : Cliente(email, clave, nombre, telefono, ruc, direccion) {
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
    ClienteCorporativo(string email, string clave, string nombre, int telefono, string ruc, string direccion) : Cliente(email, clave, nombre, telefono, ruc, direccion) {
        this->tasaDescuento = 0.10;
    }

    void asignarCategoria() {
        cout << "Ingrese la categoria: ";
        while(categoria != 'A' or categoria !='B' ){
            cin >> categoria;
        }
    }
};

class Vendedor : public Persona {
private:
    static int numeroVendedores;

public:
    double salario;

    Vendedor(int codigo, string nombre, double salario) {
        this->codigo = codigo;
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
    if (Cliente::numeroClientes <= 6)
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
                        if (it->nombre == nombre) {
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
                    while (telefono < 99999999 or telefono > 999999999) {
                        cout << "El teléfono debe tener 9 dígitos. Ingrese nuevamente: ";
                        cin >> telefono;
                    }

                    if (Cliente::numeroClientes >= 6) {
                        cout << "Agenda llena. No se puede agregar más clientes." << endl;
                        break;
                    }
                    
                    c = new ClienteCorporativo(email, clave, nombre, telefono, ruc, direccion);
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
                        if (it->nombre == nombre) {
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
                    while (telefono < 99999999 or telefono > 999999999) {
                        cout << "El teléfono debe tener 9 dígitos. Ingrese nuevamente: ";
                        cin >> telefono;
                    }

                    c = new ClienteIndividual(email, clave, nombre, telefono, ruc, direccion);
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
        cout << "Ingrese el codigo del vendedor: ";
        cin >> codigo;
        cout << "Ingrese el salario del vendedor: ";
        cin >> salario;
        Vendedor nuevoVendedor(codigo, nombre, salario);
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

    cout << "Ingrese el código del producto: ";
    cin >> codigo;
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

    Producto nuevoProducto(codigo, descripcion, precio, tipo, stock, capacidad);
    productos.push_back(nuevoProducto);
    cout << "Se agregó el nuevo producto." << endl;
}
int cont = 0 ;

void realizarVenta(vector<Cliente*>& clientes, vector<Vendedor>& vendedores, vector<Producto>& productos) {
    cont = cont+1;
    int codigoCliente;
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

    int codigoVendedor;
    cout << "Ingrese el código del vendedor: ";
    cin >> codigoVendedor;

    bool vendedorExistente = false;
    Vendedor* vendedor;
    for (auto& v : vendedores) {
        if (v.codigo == codigoVendedor) {
            vendedorExistente = true;
            vendedor = &v;
            break;
        }
    }

    if (!vendedorExistente) {
        cout << "El vendedor no existe en la lista." << endl;
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

    cout << "Realizando venta..." << endl;


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
bool compararClientes(const Cliente* x1, const Cliente* x2) {
    return x1->codigo < x2->codigo;
}

vector <Cliente*> ordenarClientes(vector <Cliente*> x) {
    sort(x.begin(), x.end(), compararClientes);
    return x;
}

void mostrarClientes(vector <Cliente*>& x) {
    cout << "|------------------|" << "--------------------|" << "-----------------|" <<endl;
    cout << "|      Codigo      |" << "      Telefono      |" << "    Categoria    |" << endl;
    cout << "|------------------|" << "--------------------|" << "-----------------|" << endl; 
    x = ordenarClientes(x);
    for(auto i : x) {
        
        cout <<"|       "<< i->codigo  <<"       |"<< "     "<< i->telefono  <<"      |" <<"        "<< i->categoria  <<"        |" <<endl;
        cout << "|------------------|" << "--------------------|" << "-----------------|" <<endl;
    }
}

template <typename T> 
bool compararPorCodigo(const T& x1, const T& x2) {
    return x1.codigo < x2.codigo;
}

template <typename T> 
void ordenarLista(vector <T> x) {
    sort(x.begin(), x.end(), compararPorCodigo);
}

void mostrarProductos(const vector<Producto>& productos) {
    cout << "|--------------|" << "----------------------------|" << "---------------------|" << endl;
    cout << "|   Codigo     |" << "        Descripcion         |" << "         Precio      |" << endl;
    cout << "|--------------|" << "----------------------------|" << "---------------------|" << endl;
    
    for(const auto& producto : productos) {
        cout << "|        " << producto.codigo << "     |" << "      " << producto.descripcion << "       |"<<"          " << producto.precio << "       |" << endl;
        cout << "|-----------------------------|" << "---------------------------|" << "---------------------|" << endl;
    }
}


void mostrarVendedores(const vector<Vendedor>& vendedores) {
    cout << "+--------------+" << "----------------------------+" << "---------------------+" <<endl;
    cout << "|   Codigo     |" << "          Nombre            |" << "       Salario       |" <<endl;
    cout << "+--------------+" << "----------------------------+" << "---------------------+" <<endl;

    for (const auto& vendedor : vendedores) {
        cout << "|     "<< vendedor.codigo << "     |"<< "      "<<vendedor.nombre << "              |"<< "       " << vendedor.salario << "        |"<<endl;
        cout << "+--------------+" << "----------------------------+" << "---------------------+" << "--------------+" << endl;
    }
}




int main() {
    vector<Cliente*> clientes;
    vector<Vendedor> vendedores;
    vector<Producto> productos;

    Cliente* c1 = new ClienteIndividual("cliente1@example.com", "clave1", "Cliente 1", 123456789, "12345", "Dirección 1");
    Cliente* c2 = new ClienteCorporativo("cliente2@example.com", "clave2", "Cliente 2", 987654321, "54321", "Dirección 2");
    Cliente* c3 = new ClienteIndividual("cliente3@example.com", "clave3", "Cliente 3", 955987654, "12345", "Dirección 3");

    clientes.push_back(c3);
    clientes.push_back(c1);
    clientes.push_back(c2);

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
            realizarVenta(clientes, vendedores, productos);
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
