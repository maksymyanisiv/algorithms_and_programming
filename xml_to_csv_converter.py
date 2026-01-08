#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Скрипт для конвертації XML файлу CommerceML у CSV формат
"""

import xml.etree.ElementTree as ET
import csv
import sys
from typing import Dict, List, Any

def find_element_ignore_ns(parent, tag_name):
    """Знаходить елемент ігноруючи namespace"""
    for child in parent:
        child_tag = child.tag.split('}')[-1] if '}' in child.tag else child.tag
        if child_tag == tag_name:
            return child
    return None

def findall_elements_ignore_ns(parent, tag_name):
    """Знаходить всі елементи ігноруючи namespace"""
    results = []
    for child in parent:
        child_tag = child.tag.split('}')[-1] if '}' in child.tag else child.tag
        if child_tag == tag_name:
            results.append(child)
    return results

def findtext_ignore_ns(parent, tag_name, default=''):
    """Знаходить текст елемента ігноруючи namespace"""
    elem = find_element_ignore_ns(parent, tag_name)
    return elem.text if elem is not None and elem.text else default

def extract_properties(requisites_element) -> Dict[str, str]:
    """Витягує всі реквізити товару в словник"""
    properties = {}
    if requisites_element is not None:
        for req in requisites_element.iter():
            req_tag = req.tag.split('}')[-1] if '}' in req.tag else req.tag
            if req_tag == 'ЗначениеРеквизита':
                name_elem = find_element_ignore_ns(req, 'Наименование')
                value_elem = find_element_ignore_ns(req, 'Значение')
                if name_elem is not None and value_elem is not None:
                    properties[name_elem.text if name_elem.text else ''] = value_elem.text if value_elem.text else ''
    return properties

def parse_товар(товар_element) -> Dict[str, Any]:
    """Парсить один елемент Товар та повертає словник з даними"""
    item = {}
    
    item['Ид'] = findtext_ignore_ns(товар_element, 'Ид')
    item['Штрихкод'] = findtext_ignore_ns(товар_element, 'Штрихкод')
    item['Артикул'] = findtext_ignore_ns(товар_element, 'Артикул')
    item['Код'] = findtext_ignore_ns(товар_element, 'Код')
    item['Наименование'] = findtext_ignore_ns(товар_element, 'Наименование')
    item['Описание'] = findtext_ignore_ns(товар_element, 'Описание')
    item['Категория'] = findtext_ignore_ns(товар_element, 'Категория')
    
    base_unit = find_element_ignore_ns(товар_element, 'БазоваяЕдиница')
    if base_unit is not None:
        item['БазоваяЕдиница_Код'] = base_unit.get('Код', '')
        item['БазоваяЕдиница_Название'] = base_unit.get('НаименованиеПолное', '')
        item['БазоваяЕдиница_Сокращение'] = base_unit.get('МеждународноеСокращение', '')
    else:
        item['БазоваяЕдиница_Код'] = ''
        item['БазоваяЕдиница_Название'] = ''
        item['БазоваяЕдиница_Сокращение'] = ''
    
    groups_element = find_element_ignore_ns(товар_element, 'Группы')
    if groups_element is not None:
        groups = []
        for g in groups_element.iter():
            g_tag = g.tag.split('}')[-1] if '}' in g.tag else g.tag
            if g_tag == 'Ид' and g.text:
                groups.append(g.text)
        item['Группы'] = '; '.join(groups)
    else:
        item['Группы'] = ''
    
    requisites = find_element_ignore_ns(товар_element, 'ЗначенияРеквизитов')
    properties = extract_properties(requisites)
    
    item['ВидНоменклатуры'] = properties.get('ВидНоменклатуры', '')
    item['ТипНоменклатуры'] = properties.get('ТипНоменклатуры', '')
    item['Полное_наименование'] = properties.get('Полное наименование', '')
    item['КатегорияНоменклатуры'] = properties.get('КатегорияНоменклатуры', '')
    item['НаименованиеПолное'] = properties.get('НаименованиеПолное', '')
    item['Склад'] = properties.get('Склад', '')
    
    return item

def convert_xml_to_csv(xml_file: str, csv_file: str, batch_size: int = 1000):
    """
    Конвертує XML файл у CSV
    
    Args:
        xml_file: шлях до вхідного XML файлу
        csv_file: шлях до вихідного CSV файлу
        batch_size: розмір пакету для обробки (для великих файлів)
    """
    print(f"Починаю обробку файлу: {xml_file}")
    print(f"Це може зайняти деякий час для великого файлу...")
    
    csv_headers = [
        'Ід', 'Штрихкод', 'Артикул', 'Код', 'Наименування', 'Описание', 
        'Категорія', 'БазоваЕдиниця_Код', 'БазоваЕдиниця_Назва', 
        'БазоваЕдиниця_Скорочення', 'Групи', 'ВидНоменклатури', 
        'ТипНоменклатури', 'Повне_найменування', 'КатегоріяНоменклатури',
        'НайменуванняПовне', 'Склад'
    ]
    
    товары_count = 0
    
    with open(csv_file, 'w', newline='', encoding='utf-8-sig') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=csv_headers, extrasaction='ignore')
        writer.writeheader()
        
        context = ET.iterparse(xml_file, events=('start', 'end'))
        context = iter(context)
        
        for event, elem in context:
            tag_without_ns = elem.tag.split('}')[-1] if '}' in elem.tag else elem.tag
            if event == 'end' and tag_without_ns == 'Товар':
                try:
                    item_data = parse_товар(elem)
                    
                    csv_row = {
                        'Ід': item_data.get('Ид', ''),
                        'Штрихкод': item_data.get('Штрихкод', ''),
                        'Артикул': item_data.get('Артикул', ''),
                        'Код': item_data.get('Код', ''),
                        'Наименування': item_data.get('Наименование', ''),
                        'Описание': item_data.get('Описание', ''),
                        'Категорія': item_data.get('Категория', ''),
                        'БазоваЕдиниця_Код': item_data.get('БазоваяЕдиница_Код', ''),
                        'БазоваЕдиниця_Назва': item_data.get('БазоваяЕдиница_Название', ''),
                        'БазоваЕдиниця_Скорочення': item_data.get('БазоваяЕдиница_Сокращение', ''),
                        'Групи': item_data.get('Группы', ''),
                        'ВидНоменклатури': item_data.get('ВидНоменклатуры', ''),
                        'ТипНоменклатури': item_data.get('ТипНоменклатуры', ''),
                        'Повне_найменування': item_data.get('Полное_наименование', ''),
                        'КатегоріяНоменклатури': item_data.get('КатегорияНоменклатуры', ''),
                        'НайменуванняПовне': item_data.get('НаименованиеПолное', ''),
                        'Склад': item_data.get('Склад', '')
                    }
                    
                    writer.writerow(csv_row)
                    товары_count += 1
                    
                    if товары_count % batch_size == 0:
                        print(f"Оброблено товарів: {товары_count}")
                    
                    elem.clear()
                    
                except Exception as e:
                    print(f"Помилка при обробці товару: {e}")
                    continue
    
    print(f"\nГотово! Оброблено товарів: {товары_count}")
    print(f"CSV файл збережено: {csv_file}")

if __name__ == "__main__":
    xml_input = "/Users/maksymyanisiv/test for cursor/import (1).xml"
    csv_output = "/Users/maksymyanisiv/test for cursor/import_products.csv"
    
    try:
        convert_xml_to_csv(xml_input, csv_output)
        print("\n✅ Конвертація успішно завершена!")
    except Exception as e:
        print(f"\n❌ Помилка: {e}")
        sys.exit(1)

