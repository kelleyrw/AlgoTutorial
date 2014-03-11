#include "SimpleTable.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>

// implementation of SimpleTable
// -----------------------------------------------------------------------------------------------------//

SimpleTable::SimpleTable()
    : width_(0)
    , height_(0)
    , defaultWidth_(4)
    , rowLabelWidth_(3)
    , colLabelHeight_(1)
    , precision_(4)
    , delineator_(" | ")
    , lend_("| ")
    , rend_(" |")
    , corner_("+")
    , out_(&std::cout)
    , file_(NULL)
    , dispTitle_(false)
    , dispLines_(false)
    , useVertColLabels_(false)
{
}

SimpleTable::~SimpleTable()
{
    if (file_ != NULL)
    {
        file_->close();
        delete file_;
    }
}

SimpleTableCellSetter SimpleTable::setCells()
{
    return SimpleTableCellSetter(*this);
}

SimpleTableColumnLabeler SimpleTable::setTable()
{
    return SimpleTableColumnLabeler(*this);
}

void SimpleTable::setCell(const std::string& entry, size_t r, size_t c){
    if (r >= table_.size()){
        std::vector<std::string> tempv;
        for (size_t i = table_.size(); i <= r; i++){
            table_.push_back(tempv);
        }
    }
    if (r >= rowLabels_.size()){
        for (size_t i = rowLabels_.size(); i <= r; i++){
            rowLabels_.push_back(" ");
        }
    }
    if (c >= table_[r].size()){
        for (size_t j = table_[r].size(); j <= c; j++){
            std::string temps;
            table_[r].push_back(temps);
        }
    }
    if (c >= colLabels_.size()){
        for (size_t i = colLabels_.size(); i <= c; i++){
            colLabels_.push_back(" ");
        }
    }
    if (c >= colWidth_.size()){
        for (size_t k = colWidth_.size(); k <= c; k++){
            colWidth_.push_back(defaultWidth_);
        }
    }

    if (colWidth_[c]<entry.length()){
        colWidth_[c] = entry.length();
    }
    if ((c + 1)>width_){ width_ = c + 1; }
    if ((r + 1)>height_){ height_ = r + 1; }
    table_[r][c] = entry;
}

void SimpleTable::setCell(const char* entryc, size_t r, size_t c){
    std::string entry = entryc;
    setCell(entry, r, c);
}

void SimpleTable::setCell(int entryi, size_t r, size_t c){
    std::stringstream ss;
    ss << entryi;
    std::string entry;
    ss >> entry;
    setCell(entry, r, c);
}

void SimpleTable::setCell(unsigned int entryu, size_t r, size_t c){
    std::stringstream ss;
    ss << entryu;
    std::string entry;
    ss >> entry;
    setCell(entry, r, c);
}

void SimpleTable::setCell(float entryf, size_t r, size_t c){
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision_) << entryf;
    std::string entry;
    ss >> entry;
    setCell(entry, r, c);
}

void SimpleTable::setCell(double entryd, size_t r, size_t c){
    std::stringstream ss;
    ss << entryd;
    std::string entry;
    ss >> entry;
    setCell(entry, r, c);
}

void SimpleTable::setTitle(const char* title){ title_ = title; }
void SimpleTable::setTitle(const std::string& title){ title_ = title; }
void SimpleTable::setPrecision(size_t precision){ precision_ = precision; }

void SimpleTable::printTitle() const {
    size_t line = calcLine();
    if ((title_.length() + 4)>line){ line = title_.length() + 4; }
    (*out_) << corner_;
    printLine('-', line - 2, false);
    (*out_) << corner_ << std::endl;
    (*out_) << lend_ << std::left << std::setw(line - 4) << title_ << std::right << rend_ << std::endl;
    (*out_) << corner_;
    printLine('-', line - 2, false);
    (*out_) << corner_ << std::endl << std::endl;
}

size_t SimpleTable::calcLine() const {
    size_t line = 0;
    line += rowLabelWidth_;
    line += 3;
    for (size_t k = 0; k<colWidth_.size(); k++){
        if (colLabels_[k].length()>colWidth_[k]){ colWidth_[k] = colLabels_[k].length(); }
        line += colWidth_[k];
        line += 3;
    }
    return line;
}

void SimpleTable::printLine(char symbol, size_t length, bool endline) const {
    for (size_t i = 0; i<length; i++){
        (*out_) << symbol;
    }
    if (endline){ (*out_) << std::endl; }
}

void SimpleTable::print() const {
    if (dispTitle_){ printTitle(); }
    if (height_>0 || width_>0){

        printColLabels();
        size_t line = calcLine();
        for (size_t i = 0; i<height_; i++){
            if (dispLines_){ printLine('-', line); }
            (*out_) << " " << std::setw(rowLabelWidth_) << std::left << rowLabels_[i] << std::right;
            (*out_) << delineator_;
            for (size_t j = 0; j<width_; j++){
                if (table_[i].size()>j){
                    (*out_) << std::setw(colWidth_[j]) << std::left << table_[i][j] << delineator_;
                }
                else{
                    (*out_) << std::setw(colWidth_[j]) << " " << delineator_;
                }
            }
            (*out_) << std::endl;
        }
        if (dispLines_){ printLine('-', line); }
    }
    else{
        (*out_) << "->  Table Empty  <-" << std::endl;

    }
}

void SimpleTable::printColLabels() const {
    if (useVertColLabels_){
        for (size_t i = 0; i<colLabels_.size(); i++){
            if (colLabels_[i].length()>colLabelHeight_){ colLabelHeight_ = colLabels_[i].length(); }
        }
        for (size_t j = 0; j<colLabelHeight_; j++){
            for (size_t k = 0; k<rowLabelWidth_ + 1; k++){
                (*out_) << " ";
            }
            for (size_t l = 0; l<colLabels_.size(); l++){
                if (j == colLabelHeight_ - 1){ (*out_) << delineator_; }
                else{ (*out_) << "   "; }
                if ((colLabelHeight_ - j)>colLabels_[l].length()){ (*out_) << std::setw(colWidth_[l]) << " "; }
                else{ (*out_) << std::setw(colWidth_[l]) << colLabels_[l][j + colLabels_[l].length() - colLabelHeight_]; }
            }
            if (j == colLabelHeight_ - 1){ (*out_) << delineator_ << std::endl;; }
            else{ (*out_) << "   " << std::endl;; }
        }
    }
    else{
        for (size_t k = 0; k<rowLabelWidth_ + 1; k++){
            (*out_) << " ";
        }
        for (size_t i = 0; i<colLabels_.size(); i++){
            if (colLabels_[i].length()>colWidth_[i]){ colWidth_[i] = colLabels_[i].length(); }
            (*out_) << delineator_ << std::setw(colWidth_[i]) << colLabels_[i];
        }
        (*out_) << delineator_ << std::endl;
    }
}

void SimpleTable::useLines(bool line){ dispLines_ = line; }
void SimpleTable::useTitle(bool title){ dispTitle_ = title; }
void SimpleTable::useVertColLabels(bool vert){ useVertColLabels_ = vert; }

void SimpleTable::setColLabel(const std::string& label, size_t c){
    if (c >= colLabels_.size()){
        for (size_t i = colLabels_.size(); i <= c; i++){
            colLabels_.push_back(" ");
            colWidth_.push_back(defaultWidth_);
        }
    }
    colLabels_[c] = label;
    if ((c + 1)>width_){ width_ = c + 1; }
}

void SimpleTable::setColLabel(const char* labelc, size_t c){
    std::string label = labelc;
    setColLabel(label, c);
}

void SimpleTable::setRowLabel(const std::string& label, size_t r){
    if (r >= rowLabels_.size()){
        for (size_t i = rowLabels_.size(); i <= r; i++){
            rowLabels_.push_back(" ");
        }
    }
    if (label.length()>rowLabelWidth_){ rowLabelWidth_ = label.length(); }
    if (r >= table_.size()){
        std::vector<std::string> tempv;
        for (size_t i = table_.size(); i <= r; i++){
            table_.push_back(tempv);
        }
    }
    rowLabels_[r] = label;
    if ((r + 1)>height_){ height_ = r + 1; }
}

void SimpleTable::setRowLabel(const char* labelc, size_t r){
    std::string label = labelc;
    setRowLabel(label, r);
}

void SimpleTable::saveAs(const std::string& filename, bool overwrite){
    if (filename.length()>0){
        if (file_ == NULL){ file_ = new std::ofstream; }
        if (file_->good()){ file_->close(); }
        if (overwrite){ file_->open(filename.c_str()); }
        else{ file_->open(filename.c_str(), std::ofstream::out | std::ofstream::app); }
        if (!file_->fail()){ out_ = file_; }
        else{
            std::cout << "Failed to open file " << filename << ", defaulting to terminal." << std::endl;
            out_ = &std::cout;
        }
    }
    else{ out_ = &std::cout; }
}

void SimpleTable::saveTex(const std::string& filename){
    if (filename.length()>0){
        if (file_ == NULL){ file_ = new std::ofstream; }
        if (file_->good()){ file_->close(); }
        file_->open(filename.c_str());
        if (!file_->fail()){ out_ = file_; }
        else{
            std::cout << "Failed to open file " << filename << ", defaulting to terminal." << std::endl;
            out_ = &std::cout;
        }
    }
    else{ out_ = &std::cout; }
    std::string cols = "c|";
    for (size_t i = 0; i<colLabels_.size(); i++){ cols += "c"; }
    (*out_) << "\\documentclass{article}" << std::endl
        << "\\begin{document}" << std::endl
        << "\\begin{table}[ht!]" << std::endl
        << "\\begin{center}" << std::endl
        << "\\begin{tabular}{" << cols << "}\\hline" << std::endl
        << " ";
    for (size_t i = 0; i<colLabels_.size(); i++){
        (*out_) << "&" << colLabels_[i];
    }
    (*out_) << "\\\\" << std::endl << "\\hline \\hline" << std::endl;
    if (height_>0 || width_>0){
        for (size_t i = 0; i<height_; i++){
            (*out_) << rowLabels_[i];
            for (size_t j = 0; j<width_; j++){
                if (table_[i].size()>j){
                    (*out_) << " & " << table_[i][j];
                }
                else{
                    (*out_) << " &  ";
                }
            }
            (*out_) << "\\\\" << std::endl;
        }
    }
    else{
        (*out_) << " & ->  Table Empty  <-" << std::endl;
    }
    (*out_) << "\\hline" << std::endl << "\\end{tabular}" << std::endl
        << "\\end{center}" << std::endl << "\\end{table}" << std::endl
        << "\\end{document}" << std::endl;
}

std::string SimpleTable::getTex() {
    using namespace std;
    std::string cols = "c|";
    for (size_t i = 0; i<colLabels_.size(); i++){ cols += "c"; }
    std::stringstream os;
    os << "\\begin{table}[ht!]" << std::endl
        << "\\begin{center}" << std::endl
        << "\\begin{tabular}{" << cols << "}\\hline" << std::endl
        << " ";
    for (size_t i = 0; i<colLabels_.size(); i++){
        os << "&" << colLabels_[i];
    }
    os << "\\\\" << std::endl << "\\hline \\hline" << std::endl;
    if (height_>0 || width_>0){
        for (size_t i = 0; i<height_; i++){
            os << rowLabels_[i];
            for (size_t j = 0; j<width_; j++){
                if (table_[i].size()>j){
                    os << " & " << table_[i][j];
                }
                else{
                    os << " &  ";
                }
            }
            os << "\\\\" << std::endl;
        }
    }
    else{
        os << " & ->  Table Empty  <-" << std::endl;
    }
    os << "\\hline" << std::endl << "\\end{tabular}" << std::endl
        << "\\end{center}" << std::endl << "\\end{table}" << std::endl;
    return os.str();
}

void SimpleTable::printTex() const {
    using namespace std;
    std::string cols = "c|";
    for (size_t i = 0; i<colLabels_.size(); i++){ cols += "c"; }
    //  cout   <<"\\documentclass{article}"<<std::endl
    //         <<"\\begin{document}"<<std::endl
    //	     <<"\\begin{table}[ht!]"<<std::endl
    cout << "\\begin{table}[ht!]" << std::endl
        << "\\begin{center}" << std::endl
        << "\\begin{tabular}{" << cols << "}\\hline" << std::endl
        << " ";
    for (size_t i = 0; i<colLabels_.size(); i++){
        cout << "&" << colLabels_[i];
    }
    cout << "\\\\" << std::endl << "\\hline \\hline" << std::endl;
    if (height_>0 || width_>0){
        for (size_t i = 0; i<height_; i++){
            cout << rowLabels_[i];
            for (size_t j = 0; j<width_; j++){
                if (table_[i].size()>j){
                    cout << " & " << table_[i][j];
                }
                else{
                    cout << " &  ";
                }
            }
            cout << "\\\\" << std::endl;
        }
    }
    else{
        cout << " & ->  Table Empty  <-" << std::endl;
    }
    cout << "\\hline" << std::endl << "\\end{tabular}" << std::endl
        << "\\end{center}" << std::endl << "\\end{table}" << std::endl;
    //<<"\\end{document}"<<std::endl;
}

std::ostream& operator << (std::ostream& os, SimpleTable& table)
{
    std::ostream* os_temp = table.out_;
    table.out_ = &os;
    table.print();
    table.out_ = os_temp;
    return os;
}