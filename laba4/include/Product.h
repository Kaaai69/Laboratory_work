#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
protected:
    int id;
    std::string name;
    double price;
    std::string type;

public:
    Product(int id, const std::string& name, double price, const std::string& type = "Generic");
    virtual ~Product() = default;

    int getId() const { return id; }
    std::string getName() const { return name; }
    double getPrice() const { return price; }


    virtual std::string getType() const { return type; }

    virtual void displayInfo() const;
    virtual double calculateTax() const { return 0.0; }

    static bool createProduct(const std::string& name, double price, const std::string& type = "physical");
    static Product* getProductById(int productId);
    static bool deleteProduct(int productId);
    static std::vector<Product*> getAllProducts();
};


class PhysicalProduct : public Product {
private:
    double weight;
    std::string dimensions;

public:
    PhysicalProduct(int id, const std::string& name, double price,
                   double weight, const std::string& dimensions);


    std::string getType() const { return "Physical"; }

    void displayInfo() const;
    double calculateTax() const { return price * 0.2; }


    double getWeight() const { return weight; }
    std::string getDimensions() const { return dimensions; }

    static bool createPhysicalProduct(const std::string& name, double price,
                                     double weight, const std::string& dimensions);
};


class DigitalProduct : public Product {
private:
    std::string fileFormat;
    double fileSize;
    std::string licenseKey;

public:
    DigitalProduct(int id, const std::string& name, double price,
                  const std::string& format, double size, const std::string& license = "");


    std::string getType() const { return "Digital"; }

    void displayInfo() const;
    double calculateTax() const { return price * 0.18; }


    std::string getFileFormat() const { return fileFormat; }
    double getFileSize() const { return fileSize; }
    std::string getLicenseKey() const { return licenseKey; }

    void generateLicenseKey();

    static bool createDigitalProduct(const std::string& name, double price,
                                    const std::string& format, double size);
};

#endif