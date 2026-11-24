/**
 * @file grupo.hpp
 * @brief Definición de los grupos.
 */
#pragma once

#include <string>

/**
 * @class Grupo
 * @brief Clase para los grupos de la base de datos.
 * @details Guarda los datos de un grupo.
 */
class Grupo {

private:

  /* El identificador del grupo. */
  int id;
  /* El nombre del grupo. */
  std::string name;
  /* La fecha de inicio del grupo. */
  std::string startDate;
  /* La fecha de fin del grupo. */
  std::string endDate;

public:

  /**
   * @brief Define el identificador del grupo.
   * @param id el identificador del grupo.
   */
  void setId(int id);

  /**
   * @brief Regresa el identificador del grupo.
   * @return el identificador del grupo.
   */
  int getId() const;

  /**
   * @brief Define el nombre del grupo.
   * @param name el nombre del grupo.
   */
  void setName(std::string name);

  /**
   * @brief Regresa el nombre del grupo.
   * @return el nombre del grupo.
   */
  std::string getName() const;

    /**
   * @brief Define la fecha de inicio del grupo.
   * @param date la fecha de inicio del grupo.
   */
  void setStartDate(std::string date);

  /**
   * @brief Regresa la fecha de inicio del grupo.
   * @return la fecha de inicio del grupo.
   */
  std::string getStartDate() const;

    /**
   * @brief Define la fecha de fin del grupo.
   * @param date la fecha de fin del grupo.
   */
  void setEndDate(std::string date);

  /**
   * @brief Regresa la fecha de fin del grupo.
   * @return la fecha de fin del grupo.
   */
  std::string getEndDate() const;
};
