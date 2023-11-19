
std::string MakeQueryString(const PersonQuery person_query, std::string quote){
    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << person_query.min_age << " and "s << person_query.max_age << " "s
              << "and Name like '%"s << quote << "%'"s;
    return query_str.str();
}

struct DBSettings{
    string_view db_name;
    int db_connection_timeout,
    bool db_allow_exceptions,
    DBLogLevel db_log_level
};

struct PersonQuery{
    int min_age;
    int max_age;
    string_view name_filter;
};

bool DBConnect(DBConnector& connector, DBHandler& db, DBSettings db_settings){
    if (settings.db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(db_settings.db_name, db_settings.db_connection_timeout);
    } else {
        db = connector.Connect(db_settings.db_name, db_settings.db_connection_timeout);
    }
    if (!db_settings.db_allow_exceptions && !db.IsOK()) {
        return false;
    }
    return true;
}



vector<Person> LoadPersons(const DB_settings db_settings, const PersonQuery person_query ) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db;
    if (!DBConnect(connector, db, db_settings)) return {};
    DBQuery query(MakeQueryString(person_query, db.Quote(person_query.name_filter)));

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}