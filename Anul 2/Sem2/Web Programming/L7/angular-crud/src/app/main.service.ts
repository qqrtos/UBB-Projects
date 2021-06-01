import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable, of } from 'rxjs'

import { Log } from './log';

@Injectable({
  providedIn: 'root'
})
export class MainService {
  private backendUrl = "http://localhost:8080/l6";
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json',
    })
  }

  constructor(private http: HttpClient) { }

  ngOnInit(): void {}

  getAllLogs(): Observable<Log[]> {
    return this.http
      .get<Log[]>(this.backendUrl+"/get_all_logs/getAllLogs.php")
  }
  
  addLog(log: Log): void {
    let url = this.backendUrl + "/add_log/addlogpost.php?type=" + log.type + "&severity=" + log.severity + "&date=" + log.date + "&userId=" + log.userId + "&text=" + log.text;
    this.http.get<string>(url);
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      console.log(error);
      return of(result as T);
    }
  }
}
