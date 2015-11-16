#ifndef PROPERTY_HPP_INCLUDED
#define PROPERTY_HPP_INCLUDED

/* mire jó: getter és setter helyettesítése egy publikus, fiktív adattaggal. */

#define PROPERTY(parent, return_type, name) Property<parent, return_type, (& parent :: set##name), (& parent :: get##name)> name{*this}

#define GETTER(value, return_type, name) \
    return_type get##name() const \
    {   return value; }
#define SETTER(value, return_type, name) \
    void set##name(return_type const& value_setter) \
    {   value = value_setter; }
#define GETTERSETTER(value, return_type, name) GETTER(value, return_type, name) SETTER(value, return_type, name)

/* property: milyen CLASS-hoz, milyen T típusú adattag,
 * melyik SETTERPTR tagfüggvény a setter, melyik GETTERPTR tagfüggvény a getter */
template <typename CLASS, typename T,
         void (CLASS::*SETTERPTR) (T const& newvalue),
         T (CLASS::*GETTERPTR) () const>
class Property
{
    CLASS& obj;
    /* copy ctor letiltása, hogy muszáj legyen megadni az új szülő
     * objektumot (különben másolódna a referencia!) */
    Property (Property const&) = delete;

public:
    /* a property szülő objektuma. ezt azért kell paraméterként átvenni,
     * mert c++ban nem lehet sehogy kitalálni egy objektumról, hogy egy
     * másik objektum része-e (subobject) */
    Property (CLASS& obj) : obj (obj) {}

    /* property beállítása */
    Property& operator= (T const& newvalue)
    {
        (obj.*SETTERPTR) (newvalue);
        return *this;
    }

    /* property lekérdezése */
    operator T () const
    {
        return (obj.*GETTERPTR) ();
    }

    /* property = property eset kezelése */
    Property& operator= (Property const& the_other)
    {
        *this = the_other.operator T&();
        return *this;
    }
};

#endif // PROPERTY_HPP_INCLUDED
