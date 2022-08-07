#include <iostream>
#include <functional>
#include <string>
#include <string_view>


/*---------------------------------------------------------------------------------------
                        =============[ association ]============
---------------------------------------------------------------------------------------*/

/*
  - unlike object composition relationships, in an association, ther is no implied whole/part
    relationship.
  - association is a weaker type of relationship between two otherwise unrelated objects.

  - to qualify as an [association], an object must have the following relationship:
    1. the associated object (member) is otherwise unrelated to the object (class)
    2. the associated object (member) can belong to more than one object (class) at a time
    3. the associated object (member) does not have its existence managed by the object (class)
    4. the associated object (member) may or may not know about the existence of the object (class)

  - the relationships between doctors and patients is a great example of an association.
  - we can say that association models as ["uses-a"] relationship.
  - the doctor "uses" the partion (to earn income); the patient uses the doctor (for health
    reason they need i guess).

  - unlike object composition, where the relationship is always unidirectional, in an
    association, the relationship may be unidirectional or bidirectional.
*/




/*---------------------------------------------------------------------------------------
                  ============[ implementing associations ]============
---------------------------------------------------------------------------------------*/

/*
  - because associatios are a broad type of relationship, they can be implemented in many
    different mays.
  - most often, associations are implemented using pointers, where the object points at the
    associated object.
*/

namespace association
{
    // since Doctor and Patient have a circular dependency, we're going to forward declare Patient
    class Patient;

    class Doctor
    {
    private:
        std::string m_name{};
        std::vector<std::reference_wrapper<const Patient>> m_patients{};

    public:
        Doctor(std::string_view name)
            : m_name{ name }
        {
        }

        const auto& getName() const { return m_name; }

        void addPatient(Patient& patient);

        friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);
    };

    class Patient
    {
    private:
        std::string m_name{};
        std::vector<std::reference_wrapper<const Doctor>> m_doctors{};

        // we're going to make addDoctor private because we don't want the public to use it
        void addDoctor(const Doctor& doctor)
        {
            m_doctors.push_back(doctor);
        }

    public:
        Patient(std::string_view name)
            : m_name{ name }
        {
        }

        const auto& getName() const { return m_name; }

        friend void Doctor::addPatient(Patient& patient);

        friend std::ostream& operator<<(std::ostream& out, const Patient& patient);
    };

    void Doctor::addPatient(Patient& patient)
    {
        m_patients.push_back(patient);
        patient.addDoctor(*this);
    }

    std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
    {
        if (doctor.m_patients.empty())
        {
            out << doctor.m_name << " has no patients right now";
            return out;
        }

        out << doctor.m_name << " is seeing patients: ";
        for (const auto& patient : doctor.m_patients)
            out << patient.get().getName() << ' ';
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const Patient& patient)
    {
        if (patient.m_doctors.empty())
        {
            out << patient.m_name << " has no doctors right now";
            return out;
        }

        out << patient.m_name << " is seeing doctors: ";
        for (const auto& doctor : patient.m_doctors)
            out << doctor.get().getName() << ' ';
        return out;
    }


    void main()
    {
        Patient dave{ "Dave" };
        Patient frank{ "Frank" };
        Patient betsy{ "Betsy" };

        Doctor james{ "James" };
        Doctor scott{ "Scott" };

        james.addPatient(dave);

        scott.addPatient(dave);
        scott.addPatient(betsy);

        std::cout << james << '\n';
        std::cout << scott << '\n';
        std::cout << dave << '\n';
        std::cout << frank << '\n';
        std::cout << betsy << '\n';
    }
}

// in general, you should avoid birectional associations if a unidirectinal one will do, as
// they add complexity and tend to be harder to write without making errors.




/*---------------------------------------------------------------------------------------
                   ============[ reflexive association ]============
---------------------------------------------------------------------------------------*/

/*
  - sometimes object may have a relationship with other objects of the same type.
  - this is called a [reflexive association].

  - a good example of a reflexive association is the relationship between a university course
    and its prerequisites (which are also university courses).
*/

namespace reflexive
{
    class Course
    {
    private:
        std::string m_name{};
        const Course* m_prerequisite{};     // for simplicity, we only consider when the prerequisite is only one course
    
    public:
        Course(std::string_view name, const Course* prerequisite = nullptr)
            : m_name{ name }
            , m_prerequisite{ prerequisite }
        {
        }
    };
}

// this can lead to a chain of associations (a course has a prerequisite, which has a
// prerequisite, etc.).




/*---------------------------------------------------------------------------------------
                ============[ associations can be indirect ]============
---------------------------------------------------------------------------------------*/

/*
  - in all of the previous cases, we've used either pointers or references to directly link
    objects together.
  - however, in an association, this is not structly required.
  - any kind of data that allows you to link two objects together suffices.

  - in the following example, we show how a Driver class can have a unidirectional association
    with a Car without actually including a Car pointer or reference member.
*/

namespace indirect_association
{
    class Car
    {
    private:
        std::string m_name{};
        int m_id{};

    public:
        Car(std::string_view name, int id)
            : m_name{ name }
            , m_id{ id }
        {
        }

        const std::string& getName() const { return m_name; }
        int getId() const { return m_id; }
    };

    // Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
    // Because it's static, we don't need to allocate an object of type CarLot to use it
    class CarLot
    {
    private:
        static Car s_carLot[4];

    public:
        CarLot() = delete; // Ensure we don't try to create a CarLot

        static Car* getCar(int id)
        {
            for (int count{ 0 }; count < 4; ++count)
            {
                if (s_carLot[count].getId() == id)
                {
                    return &(s_carLot[count]);
                }
            }

            return nullptr;
        }
    };

    // or you can include this directly using inline intialization
    Car CarLot::s_carLot[4]{ { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };

    class Driver
    {
    private:
        std::string m_name{};
        int m_carId{};          // we're associated with the Car by ID rather than pointer

    public:
        Driver(std::string_view name, int carId)
            : m_name{ name }
            , m_carId{ carId }
        {
        }

        const std::string& getName() const { return m_name; }
        int getCarId() const { return m_carId; }
    };


    void main()
    {
        Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17

        Car* car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot

        if (car)
            std::cout << d.getName() << " is driving a " << car->getName() << '\n';
        else
            std::cout << d.getName() << " couldn't find his car\n";
    }
}

// in the above example, we have a CarLot holding our cars.
// the Driver, who needs a car, doesn't have a pointer to his Cat -- instead, he has the
// ID of the car, which we can use to get the Car from the CarLot when we need it.


//=======================================================================================

int main()
{
    association::main();
    indirect_association::main();

    return 0;
}