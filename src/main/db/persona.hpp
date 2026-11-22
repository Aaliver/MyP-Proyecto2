/**
 * @file persona.hpp
 * @brief Definición de las personas.
 */
#pragma once

#include <string>

/**
 * @class Persona
 * @brief Clase para las personas de la base de datos.
 * @details Guarda datos de una persona.
 */
class Persona {

private:

  /* El identificador de la persona. */
  int id;
  /* El nombre artístico de la persona. */
  std::string stageName;
  /* El nombre real de la persona. */
  std::string realName;
  /* La fecha de nacimiento de la persona. */
  std::string birthDate;
  /* La fecha de muerte de la persona. */
  std::string deathDate;

public:

  /**
   * @brief Define el identificador de la persona.
   * @param id el identificador de la persona.
   */
  void setId(int id);

  /**
   * @brief Regresa el identificador de la persona.
   * @return el identificador de la persona.
   */
  int getId() const;

  /**
   * @brief Define el nombre artístico de la persona.
   * @param name el nombre artístico de la persona.
   */
  void setStageName(std::string name);

  /**
   * @brief Regresa el nombre artístico de la persona.
   * @return el nombre artístico de la persona.
   */
  std::string getStageName() const;

  /**
   * @brief Define el nombre real de la persona.
   * @param name el nombre real de la persona.
   */
  void setRealName(std::string name);

  /**
   * @brief Regresa el nombre real de la persona.
   * @return el nombre real de la persona.
   */
  std::string getRealName() const;

  /**
   * @brief Define la fecha de nacimiento de la persona.
   * @param date la fecha de nacimiento de la persona.
   */
  void setBirthDate(std::string date);

  /**
   * @brief Regresa la fecha de nacimiento de la persona.
   * @return la fecha de nacimiento de la persona.
   */
  std::string getBirthDate() const;

  /**
   * @brief Define la fecha de muerte de la persona.
   * @param date la fecha de muerte de la persona.
   */
  void setDeathDate(std::string date);

  /**
   * @brief Regresa la fecha de muerte de la persona.
   * @return la fecha de muerte de la persona.
   */
  std::string getDeathDate() const;
};
