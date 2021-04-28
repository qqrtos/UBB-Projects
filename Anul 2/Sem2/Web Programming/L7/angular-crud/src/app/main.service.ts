import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Inject } from '@angular/core'

@Injectable({
  providedIn: 'root'
})
export class MainService {
  private http: HttpClient;

  //constructor(@Inject(HttpClient) private http: HttpClient) { }
  constructor() { }
}
