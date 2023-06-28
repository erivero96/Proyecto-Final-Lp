#include <iostream>
#include <string>
#include <limits>
#include <vector>

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
    Persona(string email, string clave, int codigo, string nombre, int telefono) {
        this->email = email;
        this->clave = clave;
        this->codigo = codigo;
        this->nombre = nombre;
        this->telefono = telefono;
    }
};

class Cliente : public Persona {
protected:
    double tasaDescuento;

public:
    static int numeroClientes;
    char categoria;
    int ruc;
    string direccion;

    Cliente() {}
    Cliente(string email, string clave, int codigo, string nombre, int telefono, char categoria, int ruc, string direccion) : Persona(email, clave, codigo, nombre, telefono) {
        this->categoria = categoria;
        this->ruc = ruc;
        this->direccion = direccion;
        numeroClientes += 1;
    }

    friend ostream& operator<<(ostream& o, const Cliente& cliente) {
        o << "- Cliente: " << cliente.nombre << " " << cliente.codigo << " " << cliente.telefono << " " << cliente.categoria << " " << cliente.ruc << " " << cliente.direccion << endl;
        return o;
    }

    void asignarCategoria() {
        // Completar asignacion de categoria
    }
};

int Cliente::numeroClientes = 0;

class ClienteIndividual : public Cliente {
public:
    ClienteIndividual() {}
    ClienteIndividual(string email, string clave, int codigo, string nombre, int telefono, char categoria, int ruc, string direccion) : Cliente(email, clave, codigo, nombre, telefono, categoria, ruc, direccion) {
        this->tasaDescuento = 0.03;
    }
};

class ClienteCorporativo : public Cliente {
public:
    ClienteCorporativo() {}
    ClienteCorporativo(string email, string clave, int codigo, string nombre, int telefono, char categoria, int ruc, string direccion) : Cliente(email, clave, codigo, nombre, telefono, categoria, ruc, direccion) {
        this->tasaDescuento = 0.10;
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
    }
};

int Vendedor::numeroVendedores = 0;

class Producto {
public:
    int codigo;
    string descripcion;
    double precio;
    string tipo;
    int stock;
    int capacidad;

    Producto() {}
    Producto(int codigo, string descripcion, double precio, string tipo, int stock, int capacidad) {
        this->codigo = codigo;
        this->descripcion = descripcion;
        this->precio = precio;
        this->tipo = tipo;
        this->stock = stock;
        this->capacidad = capacidad;
    }
};

void limpiarPantalla() {
    system("cls");
}

int obtenerOpcion() {
    int opcion;
    while (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opción inválida. Intente nuevamente: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    char categoria;
    int ruc;
    string direccion;
    int dni;

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
        cout << "Codigo: ";
        cin >> codigo;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Dni: ";
        cin >> dni;
        cout << "Telefono: ";
        cin >> telefono;
        cout << "Categoria: ";
        cin >> categoria;
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
        while (ruc <= 9999999999 or ruc > 99999999999) {
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

        c = new ClienteCorporativo(email, clave, codigo, nombre, telefono, categoria, ruc, direccion);
        clientes.push_back(c);
        break;
    }

    case '2': {
        cout << "Ingrese los datos del cliente individual" << endl;
        cout << "Email: ";
        cin >> email;
        cout << "Clave: ";
        cin >> clave;
        cout << "Codigo: ";
        cin >> codigo;
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Telefono: ";
        cin >> telefono;
        cout << "Categoria: ";
        cin >> categoria;
        cout << "Ruc: ";
        cin >> ruc;
        cout << "Direccion: ";
        cin.ignore();
        getline(cin, direccion);

        c = new ClienteIndividual(email, clave, codigo, nombre, telefono, categoria, ruc, direccion);
        clientes.push_back(c);
        break;
    }

    default: {
        cout << "Ingresó una opción incorrecta" << endl;
        break;
    }
    }
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

void realizarVenta(vector<Cliente*>& clientes, vector<Vendedor>& vendedores, vector<Producto>& productos) {
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
    // Lógica para realizar la venta
}

int main() {
    vector<Cliente*> clientes;
    vector<Vendedor> vendedores;
    vector<Producto> productos;

    int opcion;
    do {
        cout << "----- SISTEMA DE VENTAS -----" << endl;
        cout << "1. Agregar nuevo cliente" << endl;
        cout << "2. Buscar cliente" << endl;
        cout << "3. Agregar nuevo vendedor" << endl;
        cout << "4. Agregar nuevo producto" << endl;
        cout << "5. Realizar venta" << endl;
        cout << "6. Salir" << endl;
        cout << "Elija una opción: ";
        opcion = obtenerOpcion();

        limpiarPantalla();

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
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opción inválida. Intente nuevamente." << endl;
            break;
        }

        cout << endl;
        system("pause");
        limpiarPantalla();
    } while (opcion != 6);

    return 0;
}
