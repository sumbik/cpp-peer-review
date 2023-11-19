// Дана функция ParseCitySubjson, обрабатывающая JSON-объект со списком городов конкретной страны:
void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
            country_obj["name"s].AsString(),
            country_obj["iso_code"s].AsString(),
            country_obj["phone_code"s].AsString(),
            country_obj["time_zone"s].AsString(),
        });
        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }
        for (const auto& city_json : country_obj["cities"s].AsList()) {
            const auto& city_obj = city_json.AsObject();
            cities.push_back({city_obj["name"s].AsString(), city_obj["iso_code"s].AsString(),
                          country.phone_code + city_obj["phone_code"s].AsString(), country.name, country.iso_code,
                          country.time_zone, country.languages});
        }
    }
}    